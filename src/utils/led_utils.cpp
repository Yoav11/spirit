#include <led_utils.h>

void blink_builtin() {
    digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
}
