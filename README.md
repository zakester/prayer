# prayer
A tool for calculating Muslim Prayer Times.

Installation
-
#### Windows
In Windows you can just run **`build.bat`** file and it will generate **`prayer.exe`** you can run it using cmd.

If you want to call **`prayer.exe`** from everywhere using your cmd you can just add the tool to your **Path Enviroment**.

Usage
-
```
> prayer
06:27:15 (Fajr)
07:54:18 (Sunrise)
13:02:04 (Zuhr)
15:43:10 (Asr)
18:05:50 (Maghrib)
19:27:47 (Isha)
```
use `-np` to output the next prayer and its time.
```
> prayer -np
Zuhr 13:02:04
```
use `-npr` to output the next prayer and its remaining time.
```
> prayer -npr
Zuhr 00:20:16
```

If you want to see help just do `-h` or `--help`
```
> prayer -h
-np           Outputs the next prayer and its time.
-npr          Outputs the next prayer and the remaining time.
-h --help     Outputs this list.
```

Config
-
You have to configure `prayer` to your needs to get correct callculation, your configuration file is `src/config.h`.


```C
#define PR_LAT 36.5167                        // Latitude in degrees.
#define PR_LONG 2.88333                       // Longitude in degrees.
#define PR_ELEVATION 232.55                   // Elevation above sea level in meters.

#define PR_TIME_ZONE 1.0                      // Time Zone between -14UTC to +12UTC.
#define PR_ASR_FACTOR 1                       // Factor of shadow lenght at Asr (Shafii = 1, Hanafi = 2).

#define PR_SUN_ALTITUDE_FAJR 18.0             // Sun altitude at Fajr (Fajr angle) in degrees.
#define PR_SUN_ALTITUDE_ISHA 17.0             // Sun altitude at Isha (Isha angle) in degrees.
```

Each country has their own specified angle convention for Fajr and Isha:

| Methode | Fajr Angle | Isha Angle | Description |
| :---: | :---: | :---: | --- |
| Algerian | 18° | 17° | From Algerian Ministry of Religious Affairs and Wakfs. |
| Diyanet | 18° | 17° | From Turkey's Diyanet İşleri Başkanlığı. |
| Egypt | 19.5° | 17.5° | From Egyptian General Authority Of Surevy used in Africa, Syria and Lebanon. |
| EgyptBis | 20° | 18° | Another version of calculation from Egyptian General Authority Of Surevy. |
| France15 | 15° | 15° | For France region. |
| France18 | 18° | 18° | Another method for France region. |
| Gulf | 19.5° | 90min after Maghrib | Used by Gulf region like UAE and Kuwait. |
| Islamic Society of North America (ISNA) | 15° | 15° | Used in North America i.e US and Canada. |
| JAKIM | 20° | 18° | From Jabatan Kemajuan Islam Malaysia. |
| Kemenag | 20° | 18° | From Kementerian Agama Republik Indonesia. |
| Karachi | 18° | 18° | From University of Islamic Sciences, used by Pakistan, Afganistan, Bangladesh and India. |
| Muslim World League (MWL) | 18° | 17° | Used in Europe, Far East and parts of US. |
| MUIS | 20° | 18° | From Majlis Ugama Islam Singapura. |
| Tunisia | 18° | 18° | Tunisian Ministry of Religious Affairs. |
| Tehran | 17.7° | 14° | From Institute of Geophysics at University of Tehran. |
| Umm al-Qura | 18.5° | 90min after Maghrib | From Umm al-Qura University, used Saudi Arabia. |
| UOIF | 12° | 12° | From Union Des Organisations Islamiques De France. |
