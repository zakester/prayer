#ifndef TIME_UTILS_
#define TIME_UTILS_

#include <stdint.h>

typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} HMS;

void hour_to_HMS(HMS *hms, float hours);
float time_in_decimal();

#endif // !TIME_UTILS_
