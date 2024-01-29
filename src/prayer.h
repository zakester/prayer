#ifndef PRAYER_
#define PRAYER_

#include "time_utils.h"

#define PR_NUMBER_OF_PRAYER_TIME 6

typedef struct {
  float SA_FAJR;
  float SA_SUNRISE;
  float SA_ASR;
  float SA_MAGHRIB;
  float SA_ISHA;
} PR_PrayerSunAltitude;


enum PR_PrayerTime {
  PR_FAJR,
  PR_SUNRISE,
  PR_ZUHR,
  PR_ASR,
  PR_MAGHRIB,
  PR_ISHA,
};

typedef struct {
  enum PR_PrayerTime pt;
  float sun_altitude;
  double time;
} PR_Prayer;

static void pr_prayer_sun_altitude(PR_PrayerSunAltitude *psa, float delta); // `delta` is Sun Declination

void pr_prayers(PR_Prayer *p, double jd);
void pr_fajr(PR_Prayer *p, double jd);

PR_Prayer pr_next_prayer(PR_Prayer *prayers);

const char *pr_pt_to_string(enum PR_PrayerTime pt);
const char *pr_pt_to_arabic(enum PR_PrayerTime pt);

#endif // PRAYER_
