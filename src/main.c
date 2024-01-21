#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prayer.h"
#include "time_utils.h"

// dhuha time 4° 15'. or 5°.

int main(int argc, char *argv[]) {
  Prayer prayers[NUMBER_OF_PRAYER_TIME];
  prayer(prayers);

  HMS hms;

  // if there is no args.
  if (argc == 1) {
    for (int i = 0; i < NUMBER_OF_PRAYER_TIME; ++i) {
      hour_to_HMS(&hms, prayers[i].time);
      printf("%02u:%02u:%02u (%s)\n", hms.hour, hms.min, hms.sec,
             pt_to_string(prayers[i].pt));
    }
  }

  float time_decimal = time_in_decimal();

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-np") == 0) {
      for (int i = 0; i < NUMBER_OF_PRAYER_TIME; ++i) {
        float remaining = time_decimal - prayers[i].time;
        if (time_decimal - prayers[i].time < 0) {
          hour_to_HMS(&hms, prayers[i].time);
          // TODO: for fajr we gotta use the calculation of tomorrow.
          printf("%s %02u:%02u:%02u\n", pt_to_string(prayers[i].pt), hms.hour,
                 hms.min, hms.sec);
          break;
        }
      }
    } else if (strcmp(argv[i], "-npr") == 0) {
      for (int i = 0; i < NUMBER_OF_PRAYER_TIME; ++i) {
        float remaining = time_decimal - prayers[i].time;
        if (remaining < 0) {
          hour_to_HMS(&hms, fabs(remaining));
          // TODO: for fajr we gotta use the calculation of tomorrow.
          printf("%s %02u:%02u:%02u\n", pt_to_string(prayers[i].pt), hms.hour,
                 hms.min, hms.sec);
          break;
        }
      }
    } else {
      printf("Commnad not found");
    }
  }

  return EXIT_SUCCESS;
}
