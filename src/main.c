#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "prayer.h"

// a method of how to calculate prayers.
// https://radhifadlillah.com/blog/2020-09-06-calculating-prayer-times/#sun-altitude-at-fajr-and-isha

// Requirements.
#define LAT 36.5167
#define LONG 2.88333   // 2.884194  in degrees
#define ELEVATION 232.55 // in meters
#define TIME_ZONE 1.0    // between -14UTC to +12UTC
#define ASR_FACTOR 1     // Shafii = 1, Hanafi = 2
#define SUN_ALTITUDE_FAJR 18.0
#define SUN_ALTITUDE_ISHA 18.0

#define PI 3.14159265358979323846

#define DEG_TO_RAD(degrees) ((degrees) * (PI / 180.0))
#define RAD_TO_DEG(rad) ((rad) * (180.0 / PI))
#define ACOT(x) ((PI / 2.0) - atanf(x))

void hour_to_HMS(float hours, uint8_t *h, uint8_t *m, uint8_t *s) {
  *h = (uint8_t)hours;
  float remainingMinutes = (hours - *h) * 60;
  *m = (uint8_t)remainingMinutes;
  *s = (uint8_t)((remainingMinutes - *m) * 60);
}

void output(Prayer prayer, uint8_t *h, uint8_t *m, uint8_t *s) {
}

#define DESCEND_CORECTION (0 / 60.0) // 2min.
int main(int argc, char *argv[]) {
  Prayer prayers[6];
  prayer(prayers);

  uint8_t h, m, s;

  for (int i = 0; i < 6; ++i) {
    hour_to_HMS(prayers[i].time, &h, &m, &s);
    printf("%s time: %02u:%02u:%02u\n", to_string(prayers[i].pt), h, m, s);
  }

  return EXIT_SUCCESS;
}
