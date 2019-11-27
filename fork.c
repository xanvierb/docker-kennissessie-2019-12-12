#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_LIMIT 200ULL

#define BASE 10

static int sleep_for_a_while (void)
{
    struct timespec left = {
        .tv_sec = 0,
        .tv_nsec = 0
    };
    struct timespec timeout = {
        .tv_sec = 3600,
        .tv_nsec = 0
    };

    return nanosleep(&timeout, &left) && errno != EINTR ? 1 : 0;
}

int main (int argc, char* argv[])
{
    unsigned long long int remaining = 0ULL;
    unsigned long long int limit = DEFAULT_LIMIT;

    if (argc < 2)
    {
        printf("No limit specified, will use default: %llu\n", DEFAULT_LIMIT);
    }
    else
    {
        errno = 0;
        limit = strtoull(argv[1], NULL, BASE);
        if (errno)
        {
            printf("Invalid limit specified: %s\n", argv[1]);
            printf("Will use default limit: %llu\n", DEFAULT_LIMIT);
            limit = DEFAULT_LIMIT;
        }
        else
        {
            printf("Will use chosen limit: %llu\n", limit);
        }
    }

    for(remaining = limit; remaining >= 1; remaining -= 1)
    {
        pid_t leaked = fork();
        switch(leaked)
        {
            case 0:
                return sleep_for_a_while();
            case -1:
                printf("Unable to start a subprocess at remaining limit: %llu\n", remaining);
                if (argc)
                {
                    printf("To clean up the mess, run: killall %s\n", argv[0]);
                }

                return 0;
            default:
                continue;
        }
    }

    printf("Not enough to exhaust the system, try a bigger limit: %llu\n", 2ULL * limit);
    if (argc)
    {
        printf("To clean up the mess, run: killall %s\n", argv[0]);
    }

    return 1;
}
