#include <mpu_utils.h>
#include <nrf_utils.h>

#include <Arduino.h>
#include <Ticker.h>

#define END_STREAM 000000
bool status;
int16_t incomingData[6];
int i = 0;
bool complete_set;

void setup() {
    Serial.begin(9600);
    Wire.begin();

    mpu_setup();
    network_connect();

}


void loop() {
    if( NODE_ID == 00) {
        complete_set = false;
        if(network_avaiable()) {
            incomingData[i] = network_read();
            i = (i+1) % 6;
            if(i == 0) {
                complete_set = true;
            }
        }
        if(complete_set) {
            Serial.println();
            for (int i = 0; i < 6; i++) {
                Serial.print(incomingData[i]);
                Serial.print(",");
            }
        }
    } else {
        if(millis() % 100 == 0){
            int16_t* p = mpu_get();
            for (int i = 0; i < 6; i++) {
                status = network_write(*(p+i));
            }
        }
    }
}
