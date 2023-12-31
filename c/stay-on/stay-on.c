// [2.0.0] Keep the light on all the time

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
  stdio_init_all();
  
  if (cyw43_arch_init()) {
    printf("Wi-Fi did not.");
    return -1;
  }
  while (true) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
  }
}
