// fixes error with clock_gettime
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#ifdef __linux__
	#include <sys/sysinfo.h>
#elif _WIN32
    #include <Windows.h>
#elif __APPLE__
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif


void GeneratePasswordChar() 
{
    static const char *const CHARSET = "abcdefghijklmnopqrstuvwxyz-!_@#$ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    static int cached_len;

    if (!cached_len)
        cached_len = strlen(CHARSET);

    char c = CHARSET[rand() % cached_len];
    putchar(c);
    return;
}

int GetNumberCPUs() 
{
#ifdef __linux__
    return get_nprocs_conf();
#elif _WIN32
    SYSTEM_INFO data;
    GetSystemInfo(&data);

    return data.dwNumberOfProcessors;
#elif __APPLE__
    int count;
    size_t count_len = sizeof(count);
    systemctl("hw.logicalcpu", &count, &count_len, NULL, 0);
    return count;
#else
    return (0);
#endif
}

int main(int argc, char **argv) 
{
	char line0[256]; // if you need more than that, learn to pass two arguments lmao.
	char line1[256];
	long int nanoseconds;
	uint64_t seed_1;
#if defined(__linux__) || defined(__APPLE__)
	time_t seconds;
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	nanoseconds = spec.tv_nsec;

	seed_1 = (uint64_t)nanoseconds * GetNumberCPUs() % (uint64_t)time(NULL);
#elif _WIN32
	printf("Haven't done any Windows testing with this. clock_gettime does not work there. Your seed will not include UNIX epoch or any time in it.\n");
	seed_1 = GetNumberCPUs() % 69420;
#endif

	uint64_t len, seed_2;
	switch (argc) {
		case 1:
			printf("Enter a seed: ");
			fgets(line0, sizeof(line0), stdin);
			seed_2 = strtoll(line0, NULL, 10);
			if (!seed_2) {
				printf("Enter a seed that is a number not zero.\n");
				return (-1);
			}

			printf("Enter password length: ");
			fgets(line1, sizeof(line1), stdin);
			len = strtoll(line1, NULL, 10);
			if (!len || len < 4) {
				printf("Enter a length that is a number greater than 3.\n");
				return (-1);
			}
			break;
		case 2:
			seed_2 = atoll(argv[1]);
			printf("Enter password length: ");
			fgets(line1, sizeof(line1), stdin);
			len = strtoll(line1, NULL, 10);
			if (!len || len < 4) {
				printf("Enter a length that is a number greater than 3.\n");
				return (-1);
			}
			break;
		case 3:
			seed_2 = atoll(argv[1]);
			len = atoll(argv[2]);
			if (!seed_2) {
				printf("Enter a seed that is a number not zero.\n");
				return (-1);
			}
			else if (!len || len < 4) {
				printf("Enter a length that is a number greater than 3.\n");
				return (-1);
			}
			break;
		default:
			if (argc > 3) {
				seed_2 = atoll(argv[1]);
				len = atoll(argv[2]);
				if (!seed_2) {
					printf("Enter a seed that is a number not zero.\n");
					return (-1);
				}
				else if (!len || len < 4) {
					printf("Enter a length that is a number greater than 3.\n");
					return (-1);
				}
				break;
			}
			else {
				printf("Enter a seed: ");
				fgets(line0, sizeof(line0), stdin);
				seed_2 = strtoll(line0, NULL, 10);
				if (!seed_2) {
					printf("Enter a seed that is a number not zero.\n");
					return (-1);
				}

				printf("Enter password length: ");
				fgets(line1, sizeof(line1), stdin);
				len = strtoll(line1, NULL, 10);
				if (!len || len < 4) {
					printf("Enter a length that is a number greater than 3.\n");
					return (-1);
				}
				break;
			}
	}

	srand(seed_1 * seed_2);
	for (uint64_t i = 0; i < len; i++)
		GeneratePasswordChar();

	return (0);
}