#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
#define HOUR 0.0
#define MIN 0.0
#define SEC 0.0

#define PI 3.14159265358979323846

#define DEG_TO_RAD(degrees) ((degrees) * (PI / 180.0))
#define RAD_TO_DEG(rad) ((rad) * (180.0 / PI))
#define ACOT(x) ((PI / 2.0) - atanf(x))

double gregorian_to_julian(uint16_t y, uint8_t m, uint8_t d) {
  if (m <= 2) {
    m = m + 12;
    y = y - 1;
  }

  uint8_t A = y / 100;
  int8_t B = 2 + (A / 4) - A;

  return 1720994.5 + (365.25 * y) + (uint16_t)(30.6001 * (m + 1)) + B + d +
         ((HOUR * 3600.0 + MIN * 60.0 + SEC * 60.0) / 86400.0) -
         (TIME_ZONE / 24.0);
}

double julian_day_number() {
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
         ((HOUR * 3600.0 + MIN * 60.0 + SEC * 60.0) / 86400.0) -
         (TIME_ZONE / 24.0);
}

#define EARTH_TILT 23.45
#define NOON_JAN_2000_IN_JULIAN 2451545.0
float sun_declination(double *jd) {
  float t = 2 * PI * (*jd - NOON_JAN_2000_IN_JULIAN) / 365.25;
  float A = 57.297 * t;
  float delta = 0.37877 + EARTH_TILT * sinf(DEG_TO_RAD(A - 79.547)) +
                0.3812 * sinf(DEG_TO_RAD(2 * A - 82.682)) +
                0.17132 * sinf(DEG_TO_RAD(3 * A - 59.722));
  return delta;
}

float equation_of_time(double *jd) {
  float u = (*jd - NOON_JAN_2000_IN_JULIAN) / 36525.0;
  float l0 = 280.46607 + 36000.7698 * u;

  float et1000 = -(1789 + 237 * u) * sinf(DEG_TO_RAD(l0)) -
                 (7146 - 62 * u) * cosf(DEG_TO_RAD(l0)) +
                 (9934 - 14 * u) * sinf(DEG_TO_RAD(2 * l0)) -
                 (29 + 5 * u) * cosf(DEG_TO_RAD(2 * l0)) +
                 (74 + 10 * u) * sinf(DEG_TO_RAD(3 * l0)) +
                 (320 - 4 * u) * cosf(DEG_TO_RAD(3 * l0)) -
                 212 * sinf(DEG_TO_RAD(4 * l0));
  return et1000 / 1000.0;
}

float transit_time(float *et) {
  return 12 + TIME_ZONE - (LONG / 15) - (*et / 60);
}

struct SunAltitude {
  float SA_FAJR;
  float SA_SUNRISE;
  float SA_ASR;
  float SA_MAGHRIB;
  float SA_ISHA;
} SunAltitude;

#define AR_CORRECTION -0.8333
void sun_altitude(struct SunAltitude *sa, float *sun_declination) {
  sa->SA_FAJR = -(SUN_ALTITUDE_FAJR);
  sa->SA_SUNRISE = AR_CORRECTION - (0.0347 * sqrtf(ELEVATION));
  sa->SA_ASR = RAD_TO_DEG(ACOT(ASR_FACTOR +
                               tanf(DEG_TO_RAD(fabs(LAT - *sun_declination)))));
  sa->SA_MAGHRIB = sa->SA_SUNRISE;
  sa->SA_ISHA = -(SUN_ALTITUDE_ISHA);
}

double hour_angle(float *sa, float *sun_declination) {
  float _sa = DEG_TO_RAD(*sa);
  double lat = DEG_TO_RAD(LAT);
  double delta = DEG_TO_RAD(*sun_declination);
  double cos_ha = (sin(_sa) - sin(lat) * sin(delta)) / (cos(lat) * cos(delta));

  return RAD_TO_DEG(acos(cos_ha));
}

void hour_to_HMS(float hours, uint8_t *h, uint8_t *m, uint8_t *s) {
  *h = (uint8_t)hours;
  float remainingMinutes = (hours - *h) * 60;
  *m = (uint8_t)remainingMinutes;
  *s = (uint8_t)((remainingMinutes - *m) * 60);
}

void output(double *prayer, uint8_t *h, uint8_t *m, uint8_t *s) {
  hour_to_HMS(*prayer, h, m, s);
  printf("Prayer time: %02u:%02u:%02u --- %f\n", *h, *m, *s, *prayer);
}

#define DESCEND_CORECTION (0 / 60.0) // 2min.
int main(int argc, char *argv[]) {
  double jd = julian_day_number();
  float et = equation_of_time(&jd);
  float tt = transit_time(&et);
  float sd = sun_declination(&jd);

  uint8_t h;
  uint8_t m;
  uint8_t s;

  struct SunAltitude sa;
  sun_altitude(&sa, &sd);

  double fajr = tt - (hour_angle(&sa.SA_FAJR, &sd) / 15.0);
  double sunrise = tt - (hour_angle(&sa.SA_SUNRISE, &sd) / 15.0);
  double zuhr = tt + DESCEND_CORECTION;
  double asr = tt + (hour_angle(&sa.SA_ASR, &sd) / 15.0);
  double sunset = tt + (hour_angle(&sa.SA_MAGHRIB, &sd) / 15.0);
  double isha = tt + (hour_angle(&sa.SA_ISHA, &sd) / 15.0);

  output(&fajr, &h, &m, &s);
  output(&sunrise, &h, &m, &s);
  output(&zuhr, &h, &m, &s);
  output(&asr, &h, &m, &s);
  output(&sunset, &h, &m, &s);
  output(&isha, &h, &m, &s);

  // hour_to_HMS(fajr, &h, &m, &s);
  // printf("Prayer time: %02u:%02u:%02u", h, m, s);

  return EXIT_SUCCESS;
}
