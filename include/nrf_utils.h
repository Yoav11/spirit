/*
set of helper functions for the nrf-24 wireless module
*/
#include <Arduino.h>
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#define NRF_CE 10
#define NRF_CSN 9
#define NODE_ID 00

void network_connect();
int16_t network_read();
bool network_write(int16_t data);
bool network_avaiable();
