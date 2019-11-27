#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>

#define GiB (1024ULL * 1024ULL * 1024ULL)
#define DEFAULT_LIMIT (2 * GiB)

#define BASE 10

int main (int argc, char* argv[])
{
    unsigned long long int remaining = 0ULL;
    unsigned long long int limit = DEFAULT_LIMIT;
    unsigned long long int step = (unsigned long long int) sysconf(_SC_PAGESIZE);
    size_t pageSize = (size_t) step;

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

    for(remaining = limit; remaining >= pageSize; remaining -= pageSize)
    {
        void * leaked = malloc(pageSize);
        if (leaked)
        {
            if (mlock(leaked, pageSize))
            {
                printf("Unable to pin page in memory at remaining limit: %llu\n", remaining);
            }
        }
        else
        {
            printf("Unable to allocate at remaining limit: %llu\n", remaining);
            return 0;
        }
    }

    printf("Not enough to exhaust the system, try a bigger limit: %llu\n", 2ULL * limit);
    return 1;
}
