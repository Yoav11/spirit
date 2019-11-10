#include <mpu_utils.h>

#include <Arduino.h>
#include <Ticker.h>

Ticker print_mpu(mpu_print, 1000);

void setup() {
    Serial.begin(9600);
    Wire.begin();

    mpu_setup();
    print_mpu.start();
}

void loop() {
    print_mpu.update();
}
