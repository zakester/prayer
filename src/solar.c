#include "solar.h"
#include "math_utils.h"
#include "general.h"

#include <math.h>

#define PR_AR_CORRECTION -0.8333 // Atmosphier Refliction.
#define PR_EARTH_TILT 23.45
#define PR_NOON_JAN_2000_IN_JULIAN 2451545.0

float pr_sun_declination(double jd) {
  float t = 2 * PR_PI * (jd - PR_NOON_JAN_2000_IN_JULIAN) / 365.25;
  float A = 57.297 * t;
  float delta = 0.37877 + PR_EARTH_TILT * sinf(PR_DEG_TO_RAD(A - 79.547)) +
                0.3812 * sinf(PR_DEG_TO_RAD(2 * A - 82.682)) +
                0.17132 * sinf(PR_DEG_TO_RAD(3 * A - 59.722));
  return delta;
}

float pr_equation_of_time(double jd) {
  float u = (jd - PR_NOON_JAN_2000_IN_JULIAN) / 36525.0;
  float l0 = 280.46607 + 36000.7698 * u;

  float et1000 = -(1789 + 237 * u) * sinf(PR_DEG_TO_RAD(l0)) -
                 (7146 - 62 * u) * cosf(PR_DEG_TO_RAD(l0)) +
                 (9934 - 14 * u) * sinf(PR_DEG_TO_RAD(2 * l0)) -
                 (29 + 5 * u) * cosf(PR_DEG_TO_RAD(2 * l0)) +
                 (74 + 10 * u) * sinf(PR_DEG_TO_RAD(3 * l0)) +
                 (320 - 4 * u) * cosf(PR_DEG_TO_RAD(3 * l0)) -
                 212 * sinf(PR_DEG_TO_RAD(4 * l0));
  return et1000 / 1000.0;
}

double pr_hour_angle(float angle, float delta) {
  float angle_rad = PR_DEG_TO_RAD(angle);
  double lat_rad = PR_DEG_TO_RAD(PR_LAT);
  double delta_rad = PR_DEG_TO_RAD(delta);
  double cos_ha = (sin(angle_rad) - sin(lat_rad) * sin(delta_rad)) / (cos(lat_rad) * cos(delta_rad));

  return PR_RAD_TO_DEG(acos(cos_ha));
}
