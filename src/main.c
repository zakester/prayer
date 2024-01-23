#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "julian.h"
#include "prayer.h"
#include "time_utils.h"

// dhuha time 4° 15'. or 5°.

void np_command(PR_Prayer *prayers, PR_HMS *hms);
void npr_command(PR_Prayer *prayers, PR_HMS *hms);
void npru_command(PR_Prayer *prayers, PR_HMS *hms);
void help_command();

int main(int argc, char *argv[]) {
  PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME];
  pr_prayers(prayers, pr_julian());

  PR_HMS hms;

  // if there is no args.
  if (argc == 1) {
    for (int i = 0; i < PR_NUMBER_OF_PRAYER_TIME; ++i) {
      pr_hour_to_HMS(&hms, prayers[i].time);
      printf("%02u:%02u:%02u (%s)\n", hms.hour, hms.min, hms.sec,
             pr_pt_to_string(prayers[i].pt));
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
    } else if (strcmp(argv[i], "-npru") == 0) {
      npru_command(prayers, &hms);
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

void np_command(PR_Prayer *prayers, PR_HMS *hms) {
  PR_Prayer p = pr_next_prayer(prayers);
  if (p.pt == PR_FAJR) {
    pr_fajr(&p, pr_julian_tommorow());
  }
  pr_hour_to_HMS(hms, p.time);
  // TODO: for fajr we gotta use the calculation of tomorrow.
  printf("%s %02u:%02u:%02u\n", pr_pt_to_string(p.pt), hms->hour, hms->min,
         hms->sec);
}

void npr_command(PR_Prayer *prayers, PR_HMS *hms) {
  PR_Prayer p = pr_next_prayer(prayers);

  float remaining = pr_time_in_decimal() - p.time;
  if (remaining > 0) {
    double jd = pr_julian_tommorow();
    pr_fajr(&p, jd);

    remaining = pr_time_in_decimal() - (p.time + 24.0);
  }

  pr_hour_to_HMS(hms, fabs(remaining));
  printf("%s %02u:%02u:%02u\n", pr_pt_to_string(p.pt), hms->hour, hms->min,
         hms->sec);
}

void npru_command(PR_Prayer *prayers, PR_HMS *hms) {
  PR_Prayer p = pr_next_prayer(prayers);
  float remaining = pr_time_in_decimal() - p.time;
  if (remaining > 0) {
    double jd = pr_julian_tommorow();
    pr_fajr(&p, jd);

    remaining = pr_time_in_decimal() - (p.time + 24.0);
  }

  pr_hour_to_HMS(hms, fabs(remaining));
  
  while (!(hms->sec == 0 && hms->min == 0 && hms->hour == 0)) {
    if (kbhit()) {
      char ch = getch();
      if (ch == 'q' || ch == 'Q') {
        printf("\nExist\n");
        break;
      }
    }
    printf("%s %02u:%02u:%02u\r", pr_pt_to_string(p.pt), hms->hour, hms->min,
           hms->sec);
    fflush(stdout);

    hms->sec = (hms->sec + 59) % 60;
    hms->min = (hms->min - (hms->sec == 59)) % 60;
    hms->hour = (hms->hour - (hms->min == 59 && hms->sec == 59)) % 24;

    Sleep(1000);
  }
}

void help_command() {
  printf("-np            Outputs the next prayer and its time.\n");
  printf("-npr           Outputs the next prayer and the remaining time.\n");
  printf("-npru          Outputs the next prayer and the remaining time updates in realtime. (auto exit when remaining time is 00:00:00)\n");
  // todo: -nprul
  printf("-h --help      Outputs this list.\n");
}
