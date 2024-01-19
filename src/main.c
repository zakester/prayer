#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "prayer.h"

// a method of how to calculate prayers.
// https://radhifadlillah.com/blog/2020-09-06-calculating-prayer-times/#sun-altitude-at-fajr-and-isha
// https://astronomycenter.net/pdf/subeahi_2007.pdf
// https://astronomycenter.net/paper.html
// https://eprints.um.edu.my/16657/1/0001.pdf
// dhuha time 4° 15'. or 5°.

void hour_to_HMS(float hours, uint8_t *h, uint8_t *m, uint8_t *s) {
  *h = (uint8_t)hours;
  float remainingMinutes = (hours - *h) * 60;
  *m = (uint8_t)remainingMinutes;
  *s = (uint8_t)((remainingMinutes - *m) * 60);
}

int main(int argc, char *argv[]) {
  Prayer prayers[NUMBER_OF_PRAYER_TIME];
  prayer(prayers);

  uint8_t h, m, s;

  for (int i = 0; i < NUMBER_OF_PRAYER_TIME; ++i) {
    hour_to_HMS(prayers[i].time, &h, &m, &s);
    printf("time: %02u:%02u:%02u (%s)\n", h, m, s, pt_to_string(prayers[i].pt));
  }

  return EXIT_SUCCESS;
}
