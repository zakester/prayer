#include "prayer.h"
#include "general.h"
#include "math_utils.h"
#include "solar.h"

#include <math.h>
#include <stdint.h>

#define PR_AR_CORRECTION -0.8333 // Atmosphier Refliction.
#define PR_EARTH_TILT 23.45
#define PR_NOON_JAN_2000_IN_JULIAN 2451545.0
#define PR_TRANSIT_TIME(et) ((12 + PR_TIME_ZONE) - (PR_LONG / 15) - (et / 60))
#define PR_DESCEND_CORECTION (2 / 60.0) // 2min.

void pr_prayer_sun_altitude(PR_PrayerSunAltitude *psa, float delta) {
  psa->SA_FAJR = -(PR_SUN_ALTITUDE_FAJR);
  psa->SA_SUNRISE = PR_AR_CORRECTION - (0.0347 * sqrtf(PR_ELEVATION));
  psa->SA_ASR =
      PR_RAD_TO_DEG(PR_ACOT(PR_ASR_FACTOR + tanf(PR_DEG_TO_RAD(fabs(PR_LAT - delta)))));
  psa->SA_MAGHRIB = psa->SA_SUNRISE;
  psa->SA_ISHA = -(PR_SUN_ALTITUDE_ISHA);
}

void pr_prayers(PR_Prayer *p, double jd) {
  float delta, et;
  delta = pr_sun_declination(jd), et = pr_equation_of_time(jd);

  PR_PrayerSunAltitude psa;
  pr_prayer_sun_altitude(&psa, delta);

  float tt = PR_TRANSIT_TIME(et);
  PR_Prayer pr[PR_NUMBER_OF_PRAYER_TIME] = {
      {PR_FAJR, psa.SA_FAJR, tt - pr_hour_angle(psa.SA_FAJR, delta) / 15.0},
      {PR_SUNRISE, psa.SA_SUNRISE, tt - pr_hour_angle(psa.SA_SUNRISE, delta) / 15.0},
      {PR_ZUHR, PR_DESCEND_CORECTION, tt + PR_DESCEND_CORECTION},
      {PR_ASR, psa.SA_ASR, tt + pr_hour_angle(psa.SA_ASR, delta) / 15.0},
      {PR_MAGHRIB, psa.SA_MAGHRIB, tt + pr_hour_angle(psa.SA_MAGHRIB, delta) / 15.0},
      {PR_ISHA, psa.SA_ISHA, tt + pr_hour_angle(psa.SA_ISHA, delta) / 15.0},
  };

  for (uint8_t i = 0; i < PR_NUMBER_OF_PRAYER_TIME; ++i) {
    p[i] = pr[i];
  }
}

void pr_fajr(PR_Prayer *p, double jd) {
  float delta, et;
  delta = pr_sun_declination(jd), et = pr_equation_of_time(jd);
  PR_PrayerSunAltitude psa;
  pr_prayer_sun_altitude(&psa, delta);

  float tt = PR_TRANSIT_TIME(et);

  p->pt = PR_FAJR;
  p->sun_altitude = psa.SA_FAJR;
  p->time = tt - pr_hour_angle(psa.SA_FAJR, delta) / 15.0;
}

PR_Prayer pr_next_prayer(PR_Prayer *prayers) {
  for (int i = 0; i < PR_NUMBER_OF_PRAYER_TIME; ++i) {
    if (pr_time_in_decimal() - prayers[i].time < 0) {
      return prayers[i];
    }
  }
  return prayers[0];
}

const char *pr_pt_to_string(enum PR_PrayerTime pt) {
  switch (pt) {
  case PR_FAJR:
    return "Fajr";
  case PR_SUNRISE:
    return "Sunrise";
  case PR_ZUHR:
    return "Zuhr";
  case PR_ASR:
    return "Asr";
  case PR_MAGHRIB:
    return "Maghrib";
  case PR_ISHA:
    return "Isha";
  }
}

const char *pr_pt_to_arabic(enum PR_PrayerTime pt) {
  switch (pt) {
  case PR_FAJR:
    return "الفجر";
  case PR_SUNRISE:
    return "شروق الشمس";
  case PR_ZUHR:
    return "الظهر";
  case PR_ASR:
    return "العصر";
  case PR_MAGHRIB:
    return "المغرب";
  case PR_ISHA:
    return "العشاء";
  }
}
