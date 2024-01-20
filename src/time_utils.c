#include "time_utils.h"
#include <stdint.h>
#include <time.h>

void hour_to_HMS(HMS *hms, float hours) {
  hms->hour = (uint8_t)hours;
  float remainingMinutes = (hours - hms->hour) * 60;
  hms->min = (uint8_t)remainingMinutes;
  hms->sec = (uint8_t)((remainingMinutes - hms->min) * 60);
}

void HMS_to_hour() {}

float time_in_decimal() {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);
  return date.tm_hour + date.tm_min * 1 / 60.0 + date.tm_sec * 1 / 3600.0;
}