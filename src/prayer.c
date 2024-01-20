#include "prayer.h"
#include "general.h"
#include "julian.h"
#include "math_utils.h"
#include "solar.h"

#include <math.h>
#include <stdint.h>

#define AR_CORRECTION -0.8333 // Atmosphier Refliction.
#define EARTH_TILT 23.45
#define NOON_JAN_2000_IN_JULIAN 2451545.0
#define TRANSIT_TIME(et) ((12 + TIME_ZONE) - (LONG / 15) - (et / 60))
#define DESCEND_CORECTION (2 / 60.0) // 2min.

void prayer_sun_altitude(PrayerSunAltitude *psa, float delta) {
  psa->SA_FAJR = -(SUN_ALTITUDE_FAJR);
  psa->SA_SUNRISE = AR_CORRECTION - (0.0347 * sqrtf(ELEVATION));
  psa->SA_ASR =
      RAD_TO_DEG(ACOT(ASR_FACTOR + tanf(DEG_TO_RAD(fabs(LAT - delta)))));
  psa->SA_MAGHRIB = psa->SA_SUNRISE;
  psa->SA_ISHA = -(SUN_ALTITUDE_ISHA);
}

void prayer(Prayer *p) {
  double jd = julian();
  float delta, et;
  delta = sun_declination(jd), et = equation_of_time(jd);

  PrayerSunAltitude psa;
  prayer_sun_altitude(&psa, delta);

  float tt = TRANSIT_TIME(et);
  Prayer pr[NUMBER_OF_PRAYER_TIME] = {
      {FAJR, psa.SA_FAJR, tt - hour_angle(psa.SA_FAJR, delta) / 15.0},
      {SUNRISE, psa.SA_SUNRISE, tt - hour_angle(psa.SA_SUNRISE, delta) / 15.0},
      {ZUHR, DESCEND_CORECTION, tt + DESCEND_CORECTION},
      {ASR, psa.SA_ASR, tt + hour_angle(psa.SA_ASR, delta) / 15.0},
      {MAGHRIB, psa.SA_MAGHRIB, tt + hour_angle(psa.SA_MAGHRIB, delta) / 15.0},
      {ISHA, psa.SA_ISHA, tt + hour_angle(psa.SA_ISHA, delta) / 15.0},
  };

  for (uint8_t i = 0; i < NUMBER_OF_PRAYER_TIME; ++i) {
    p[i] = pr[i];
  }
}


enum PrayerTime next_prayer(Prayer *p) {

}

const char *pt_to_string(enum PrayerTime pt) {
  switch (pt) {
  case FAJR:
    return "Fajr";
  case SUNRISE:
    return "Sunrise";
  case ZUHR:
    return "Zuhr";
  case ASR:
    return "Asr";
  case MAGHRIB:
    return "Maghrib";
  case ISHA:
    return "Isha";
  }
}
