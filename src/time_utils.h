#ifndef TIME_UTILS_

#include <stdint.h>

typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} HMS;

void hour_to_HMS(HMS *hms, float hours);

void HMS_to_hour();

float time_in_decimal();

#endif // !TIME_UTILS_
