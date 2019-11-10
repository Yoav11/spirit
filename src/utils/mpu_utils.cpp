#include <mpu_utils.h>


// converts int16 to string
char* convert_int16_to_str(int16_t i) {
    char tmp_str[7];
    char *t_str = tmp_str;

    sprintf(tmp_str, "%6d", i);
    return t_str;
}
// setup i2c communication with the board
void mpu_setup() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}

// prints all mpu readings with labels
void mpu_print_pretty() {

    int16_t accelerometer_x, accelerometer_y, accelerometer_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temperature;

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);

    accelerometer_x = Wire.read()<<8 | Wire.read();
    accelerometer_y = Wire.read()<<8 | Wire.read();
    accelerometer_z = Wire.read()<<8 | Wire.read();
    temperature = Wire.read()<<8 | Wire.read();
    gyro_x = Wire.read()<<8 | Wire.read();
    gyro_y = Wire.read()<<8 | Wire.read();
    gyro_z = Wire.read()<<8 | Wire.read();

    Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
    Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
    Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));

    Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
    Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
    Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
    Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
    Serial.println();
}

// prints all acc and gyro readings with comma separation
void mpu_print() {
    int16_t accelerometer_x, accelerometer_y, accelerometer_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temperature;

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);

    accelerometer_x = Wire.read()<<8 | Wire.read();
    accelerometer_y = Wire.read()<<8 | Wire.read();
    accelerometer_z = Wire.read()<<8 | Wire.read();
    temperature = Wire.read()<<8 | Wire.read();
    gyro_x = Wire.read()<<8 | Wire.read();
    gyro_y = Wire.read()<<8 | Wire.read();
    gyro_z = Wire.read()<<8 | Wire.read();

    Serial.print(convert_int16_to_str(accelerometer_x)); Serial.print(",");
    Serial.print(convert_int16_to_str(accelerometer_y)); Serial.print(",");
    Serial.print(convert_int16_to_str(accelerometer_z)); Serial.print(",");

    Serial.print(convert_int16_to_str(gyro_x)); Serial.print(",");
    Serial.print(convert_int16_to_str(gyro_y)); Serial.print(",");
    Serial.print(convert_int16_to_str(gyro_z));
    Serial.println();
}
