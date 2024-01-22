#ifndef TIME_UTILS_
#define TIME_UTILS_

#include <stdint.h>

typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} PR_HMS;

void pr_hour_to_HMS(PR_HMS *hms, float hours);
float pr_time_in_decimal();

#endif // !TIME_UTILS_
