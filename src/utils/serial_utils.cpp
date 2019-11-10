#include <serial_utils.h>

// prints the time in ms since the board is on
void print_time() {
    Serial.print("Time:    ");
    Serial.println(millis());
}

//prints the address of any i2c device found
void print_addr() {
    byte error, address;
    int nDevices;
    Serial.println("scanning for i2c devices");
    nDevices = 0;
    for(address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
          Serial.print("I2C device found at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
          nDevices++;
        }
        else if (error==4) {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
        }
    }
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");
}
