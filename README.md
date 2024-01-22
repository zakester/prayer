# prayer
A tool for calculating Muslim Prayer Times.

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

Installation
-
#### Windows
In Windows you can just run **`build.bat`** file and it will generate **`prayer.exe`** you can run it using cmd.

If you want to call **`prayer.exe`** from everywhere using your cmd you can just add the tool to your **Path Enviroment**.
