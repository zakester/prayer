#ifndef SOLAR_
#define SOLAR_

typedef struct {
  float SA_FAJR;
  float SA_SUNRISE;
  float SA_ASR;
  float SA_MAGHRIB;
  float SA_ISHA;
} SunAltitude;

//void sun_altitude(SunAltitude *sa, float delta); // `delta` is Sun Declination
float sun_declination(double jd);                // `jd` is Julian Day Number
float equation_of_time(double jd);
double hour_angle(float angle, float delta);     // angle in degrees.

#endif // SOLAR_
