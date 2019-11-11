#include <mpu_utils.h>
#include <nrf_utils.h>

#include <Arduino.h>
#include <Ticker.h>

Ticker print_mpu(mpu_print, 1000);

const int data = 123;

void setup() {
    Serial.begin(9600);
    Wire.begin();

    mpu_setup();
    network_connect();

}

void loop() {
    if( NODE_ID == 00) {
        if(network_avaiable()) {
            uint16_t incomingData = network_read();
            Serial.println(incomingData);
        }
    } else {
        if(millis() % 1000 == 0){
            bool status = network_write(data);
            Serial.println(status);
        }
    }
}
