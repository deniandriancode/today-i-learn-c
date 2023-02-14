#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void timer_run(char *dur);
void timer_format(int idur);

/* TODO: Use regex to detect error of user input */
/* TODO: Add miniaudio to playback simple sound when finish */
/* TODO: Use termios to change the attribute of terminal (keypress detection) */
/* TODO: Add argument parser */
int
main(int argc, char **argv)
{
    /* get argument number */
    switch (argc) {
        case 1:
            fprintf(stderr, "Please provide duration time\n");
            return EXIT_FAILURE;
        case 2:
            timer_run(*(argv + 1));
            break;
        default:
            fprintf(stderr, "Argument must exactly one: Expected 1 get %d\n", argc);
            return EXIT_FAILURE;
    }

    /* count down to zero */

    /* finish */
    return EXIT_SUCCESS;
}

/* main timer function */
void
timer_run(char *dur)
{
    int idur;
    
    idur = (int) strtoul(dur, NULL, 10);
    if (idur < 0) { /* negative duration, exit program */
        fprintf(stderr, "Duration cannot less than zero\n");
        exit(EXIT_FAILURE);
    } else if (idur == 0) { /* either 0 or non number, exit program */
        printf("Finish\n");
        exit(EXIT_SUCCESS);
    }

    timer_format(idur);
}

/* format the display */
void
timer_format(int idur)
{
    int h, m, s;
    int count;

    count = idur;

    printf("\033[34m");
    while (count > 0) {
        h = count / 60 / 60;
        m = count / 60;
        s = count % 60;
        printf("%d:%d:%d ", h, m, s);
        printf("Remaining: %d second(s)\n", s);
        --count;
        sleep(1);
        printf("\033[A\033[K");
    }
    printf("Finish\n");
    printf("\033[0m");
}
