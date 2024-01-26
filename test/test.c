#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  uint8_t sec = 1;
  uint8_t min = 1;
  uint8_t hour = 2;

  for (int i = 0; i < 100; ++i) {
    sec = (sec + 59) % 60;
    min = (min + (sec == 59) * 59) % 60;
    hour = (hour - (min == 59 && sec == 59)) % 24;

    printf("%02u:%02u:%02u\n", hour, min, sec);
  }

  return EXIT_SUCCESS;
}
