#include <led_utils.h>

void blink_blue() {
    digitalWrite(BLUE_LED, !(digitalRead(BLUE_LED)));
}
