#ifndef CONFIG_
#define CONFIG_

// NOTE: EACH TIME YOU CHANGE THIS YOU HAVE TO RE-COMPILE THE TOOL.
#define PR_LAT 36.5167                        // Latitude in degrees.
#define PR_LONG 2.88333                       // Longitude in degrees.
#define PR_ELEVATION 232.55                   // Elevation above sea level in meters.

#define PR_TIME_ZONE 1.0                      // Time Zone between -14UTC to +12UTC.
#define PR_ASR_FACTOR 1                       // Factor of shadow lenght at Asr (Shafii = 1, Hanafi = 2).

#define PR_SUN_ALTITUDE_FAJR 18.0             // Sun altitude at Fajr (Fajr angle) in degrees.
#define PR_SUN_ALTITUDE_ISHA 17.0             // Sun altitude at Isha (Isha angle) in degrees.
//#define PR_SUN_ALTITUDE_ISHA 90.0           In case of Umm al-Qura and Gulf just use 90.0 and it will calculate Isha as Maghrib + 1h30min.

#endif // CONFIG_
