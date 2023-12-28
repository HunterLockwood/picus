/* 
  Because what else am I supposed to do, 
    learn Python?
*/

int main() {
  #ifndef PICO_DEFAULT_LED_PIN
  #warning This example requires a board with a regular LED.
  #else
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(842);
    gpio_put(LED_PIN, 0);
    sleep_ms(842);
  }
#endif
}
