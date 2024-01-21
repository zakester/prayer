#ifndef PRAYER_
#define PRAYER_

#include "time_utils.h"
#define NUMBER_OF_PRAYER_TIME 6

typedef struct {
  float SA_FAJR;
  float SA_SUNRISE;
  float SA_ASR;
  float SA_MAGHRIB;
  float SA_ISHA;
} PrayerSunAltitude;


enum PrayerTime {
  FAJR,
  SUNRISE,
  ZUHR,
  ASR,
  MAGHRIB,
  ISHA,
};

typedef struct {
  enum PrayerTime pt;
  float sun_altitude;
  double time;
} Prayer;

void prayer_sun_altitude(PrayerSunAltitude *psa, float delta); // `delta` is Sun Declination
void prayer(Prayer *p);

Prayer next_prayer(Prayer *prayers);

const char *pt_to_string(enum PrayerTime pt);
const char *pt_to_arabic(enum PrayerTime pt);

#endif // PRAYER_
