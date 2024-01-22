#include "julian.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "general.h"

#define PR_HOUR 0.0
#define PR_MIN 0.0
#define PR_SEC 0.0

double pr_gregorian_to_julian(uint16_t y, uint8_t m, uint8_t d) {
  if (m <= 2) {
    m = m + 12;
    y = y - 1;
  }

  uint8_t A = y / 100;
  int8_t B = 2 + (A / 4) - A;

  return 1720994.5 + (365.25 * y) + (uint16_t)(30.6001 * (m + 1)) + B + d +
         ((PR_HOUR * 3600.0 + PR_MIN * 60.0 + PR_SEC * 60.0) / 86400.0) -
         (PR_TIME_ZONE / 24.0);
}

double pr_julian() {
  float jd = 0.0;

  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  uint16_t y = date.tm_year + 1900;
  uint8_t m = date.tm_mon + 1;
  uint8_t d = date.tm_mday;

  if (m <= 2) {
    m = m + 12;
    y = y - 1;
  }

  uint8_t A = y / 100;
  int8_t B = 2 + (A / 4) - A;

  return 1720994.5 + (365.25 * y) + (30.6001 * m + 30.6001) + B + d +
         ((PR_HOUR * 3600.0 + PR_MIN * 60.0 + PR_SEC * 60.0) / 86400.0) -
         (PR_TIME_ZONE / 24.0);
}
