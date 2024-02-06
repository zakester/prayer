#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winbase.h>

#include "julian.h"
#include "prayer.h"
#include "time_utils.h"

// dhuha time 4° 15'. or 5°.

void np_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms);
void npr_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms);
void npru_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms, boolean loop);
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
      boolean loop = argc == 3 && (strcmp(argv[i + 1], "-l") == 0 ||
                                   strcmp(argv[i + 1], "--loop") == 0);
      if (argc == 3 && !loop) {
        printf(
            "`%s` is not a prayer command. See `prayer -h` or `prayer --help`",
            argv[i + 1]);
        break;
      }

      npru_command(prayers, &hms, loop);
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

void np_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms) {
  PR_Prayer p = pr_next_prayer(prayers);
  if (p.pt == PR_FAJR) {
    pr_fajr(&p, pr_julian_tommorow());
  }
  pr_hour_to_HMS(hms, p.time);
  // TODO: for fajr we gotta use the calculation of tomorrow.
  printf("%s %02u:%02u:%02u\n", pr_pt_to_string(p.pt), hms->hour, hms->min,
         hms->sec);
}

void npr_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms) {
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

void npru_command(PR_Prayer prayers[PR_NUMBER_OF_PRAYER_TIME], PR_HMS *hms, boolean loop) {
  PR_Prayer p = pr_next_prayer(prayers);
  boolean loop_exit = FALSE;

next_prayer:
  p = pr_next_prayer(prayers);

  do {
    if (kbhit()) {
      char ch = getch();
      if (ch == 'q' || ch == 'Q') {
        loop_exit = TRUE;
        printf("\nExist\n");
        break;
      }
    }

    float remaining = pr_time_in_decimal() - p.time;
    if (remaining > 0) {
      double jd = pr_julian_tommorow();
      pr_fajr(&p, jd);

      remaining = pr_time_in_decimal() - (p.time + 24.0);
    }
    pr_hour_to_HMS(hms, fabs(remaining));

    printf("%s %02u:%02u:%02u         \r", pr_pt_to_string(p.pt), hms->hour,
           hms->min, hms->sec);

    Sleep(1000);
  } while (!(hms->sec == 0 && hms->min == 0 && hms->hour == 0));

  if (!loop_exit && loop) {
    goto next_prayer;
  }
}

void help_command() {
  printf("-np            Outputs the next prayer and its time.\n");
  printf("-npr           Outputs the next prayer and the remaining time.\n");
  printf("-npru          Outputs the next prayer and the remaining time "
         "updates in realtime,\n"
         " command will auto exit when remaining time is 00:00:00, if you want "
         "to loop use -npru -l instead.\n");
  printf("-npru -l       When remaining time is 00:00:00, countdown for the "
         "next prayer will start.\n");
  printf("-h --help      Outputs this list.\n");
}
