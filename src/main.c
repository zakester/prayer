#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prayer.h"
#include "time_utils.h"

// dhuha time 4° 15'. or 5°.

void np_command(Prayer *prayers, HMS *hms);
void npr_command(Prayer *prayers, HMS *hms);
void help_command();

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
    return EXIT_SUCCESS;
  }

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-np") == 0) {
      np_command(prayers, &hms);
      break;
    } else if (strcmp(argv[i], "-npr") == 0) {
      npr_command(prayers, &hms);
      break;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      help_command();
      break;
    } else {
      printf("`%s` is not a prayer command. See `prayer -h` or `prayer --help`",
             argv[i]);
      break;
    }
  }
  return EXIT_SUCCESS;
}

void np_command(Prayer *prayers, HMS *hms) {
  Prayer p = next_prayer(prayers);
  hour_to_HMS(hms, p.time);
  // TODO: for fajr we gotta use the calculation of tomorrow.
  printf("%s %02u:%02u:%02u\n", pt_to_string(p.pt), hms->hour, hms->min,
         hms->sec);
}

void npr_command(Prayer *prayers, HMS *hms) {
  Prayer p = next_prayer(prayers);
  float remaining = time_in_decimal() - p.time;
  remaining = remaining < 0 ? remaining : time_in_decimal() - (p.time + 24.0);
  hour_to_HMS(hms, fabs(remaining));
  // TODO: for fajr we gotta use the calculation of tomorrow.
  printf("%s %02u:%02u:%02u\n", pt_to_string(p.pt), hms->hour, hms->min,
         hms->sec);
}

void help_command() {
  printf("-np           Outputs the next prayer and its time.\n");
  printf("-npr          Outputs the next prayer and the remaining time.\n");
  printf("-h --help     Outputs this list.\n");
}
