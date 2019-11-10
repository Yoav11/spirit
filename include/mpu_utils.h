/*
set of helper functions for the GY-521 MPU
*/
#include <Arduino.h>
#include <Wire.h>

#define MPU_ADDR 0x68

void mpu_setup();
void mpu_print_pretty();
void mpu_print();
