#include <mpu_utils.h>
#include <nrf_utils.h>
#include <led_utils.h>

#include <Arduino.h>
#include <Ticker.h>
#include <SD.h>

String headers = "0_ACC_X,0_ACC_Y,0_ACC_Z,0_GYR_X,0_GYR_Y,0_GYR_Z,1_ACC_X,1_ACC_Y,1_ACC_Z,1_GYR_X,1_GYR_Y,1_GYR_Z";
bool status;
int16_t incomingData[7];
int i = 0;
bool complete_set;

File myFile;
int name_index = 0;
char file_name [13];

float blink_count = 0;

void setup() {
    Serial.begin(9600);
    if( NODE_ID == 00) {
        if (!SD.begin(4)) {
            Serial.println("initialization failed!");
            while (1);
        }
        myFile = SD.open("meta.txt");
        if(myFile) {
            while(myFile.available()) {
                if(myFile.read() == 112){
                    name_index++;
                }
            }
            myFile.close();
        }
        sprintf(file_name, "spr%d.csv", name_index);
        myFile = SD.open("meta.txt", FILE_WRITE);
        if(myFile) {
            myFile.println(file_name);
            myFile.close();
        }

        myFile = SD.open(file_name, FILE_WRITE);
        if(myFile){
            Serial.println("writing file ..");
            myFile.println(headers);
            myFile.close();
        }
    }

    pinMode(BLUE_LED, OUTPUT);
    Wire.begin();
    mpu_setup();
    network_connect();
}

void loop() {
    if( NODE_ID == 00) {
        complete_set = false;
        if(network_avaiable()) {
            incomingData[i] = network_read();
            i = (i+1) % 7;
            if(i == 0) {
                complete_set = true;
            }
        }
        if(complete_set) {
            int16_t* p = mpu_get();
            myFile = SD.open(file_name, FILE_WRITE);
            if(myFile) {
                for (int i = 0; i < 6; i++) {
                    myFile.print(*(p+i));
                    myFile.print(",");
                }
                for (int i = 1; i < 7; i++) {
                    myFile.print(incomingData[i]);
                    myFile.print(",");
                }
                myFile.println();
                myFile.close();
                if(millis() - blink_count >= 1000) {
                    blink_count = millis();
                    blink_blue();
                }
            }
        }
    } else {
        if(millis() % 100 == 0){
            int16_t* p = mpu_get();
            status = network_write(1);
            if(status){
                for (int i = 0; i < 6; i++) {
                    status = network_write(*(p+i));
                }
                if(status && millis() - blink_count >= 1000) {
                    blink_count = millis();
                    blink_blue();
                }
            }
        }
    }
}
