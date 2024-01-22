#ifndef SOLAR_
#define SOLAR_

typedef struct {
  float SA_FAJR;
  float SA_SUNRISE;
  float SA_ASR;
  float SA_MAGHRIB;
  float SA_ISHA;
} PR_SunAltitude;

//void sun_altitude(SunAltitude *sa, float delta); // `delta` is Sun Declination
float pr_sun_declination(double jd);                // `jd` is Julian Day Number
float pr_equation_of_time(double jd);
double pr_hour_angle(float angle, float delta);     // angle in degrees.

#endif // SOLAR_
