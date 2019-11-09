#include <serial_utils.h>

void print_time() {
    Serial.print("Time:    ");
    Serial.println(millis());
}
