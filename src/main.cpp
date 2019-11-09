#include <led_utils.h>
#include <serial_utils.h>
#include <global_utils.h>

#include <Arduino.h>
#include <Ticker.h>

Ticker led_toggle(blink_builtin, 1000);
Ticker serial_time(print_time, 1000);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  led_toggle.start();
  serial_time.start();
}

void loop() {
  led_toggle.update();
  serial_time.update();
}
