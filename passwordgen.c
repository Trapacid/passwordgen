// fixes error with clock_gettime
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void GeneratePassword(int x, int y) 
{
	static const char *const CHARSET = "abcdefghijklmnopqrstuvwxyz-!_@#$ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	char character[x];
	character[y] = CHARSET[rand() % (strlen(CHARSET) - 1)];
	putchar(character[y]);
	return;
}

int main(int argc, char **argv) 
{
	char line0[256]; // if you need more than that, learn to pass two arguments lmao.
	char line1[256];

	long int nanoseconds;
	uint64_t seed_1;
	time_t seconds;
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	seconds = spec.tv_sec;
	nanoseconds = spec.tv_nsec;

	seed_1 = (uint64_t)nanoseconds * 69420 + (uint64_t)seconds;

	uint32_t len, seed_2;
	if (argc <= 2) {
		printf("input seed: ");
		fgets(line0, sizeof(line0), stdin);
		seed_2 = strtol(line0, NULL, 10);
		if (!seed_2) {
				printf("enter a number that is not 0 or characters\n");
				return -1;
		}

		printf("enter length: ");
		fgets(line1, sizeof(line1), stdin);
		len = strtol(line1, NULL, 10);
		if (!len || len <= 3) {
			printf("enter a number that is greater than 3 for length\n");
			return -1;
		}
	}
	else {
		seed_2 = atoi(argv[1]);
		len = atoi(argv[2]);
		if (!seed_2)
		{
			printf("enter a number that is not 0 or letters for seed\n");
			return -1;
		}
		if (!len || len <= 3) {
			printf("enter a number greater than 3 for length\n");
			return -1;
		}
	}
	srand(seed_1 * seed_2);
	for (int i = 0; i < len; i++)
		GeneratePassword(len, i);

	return 0;
}