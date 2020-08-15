#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ctype.h>

#define BILLION 1000000000L

int main(int argc, char **argv) {
	long int nanoseconds;
	uint64_t all;
	time_t seconds;
	struct timespec spec;
	
	clock_gettime(CLOCK_REALTIME, &spec);
	seconds = spec.tv_sec;
	nanoseconds = spec.tv_nsec;

	all = (uint64_t)seconds * BILLION + (uint64_t)nanoseconds;

	uint32_t seed;
	if(argc <= 1) {
		printf("input seed: ");
		int how;
		if(scanf("%d", &how) == 1) {
			if(how == 0) {
				printf("enter a number that is not 0 or characters fr2\n");
				return 1;
			}
			else 
				seed = how;
		}
		else {
			printf("enter a number that is not 0 or characters frcoal\n");
			return 1;
		}
	}
	else {
		int ok = atoi(argv[1]);
		if(ok == 0)
		{
			printf("enter a number that is not 0 or letters frcoal\n");
			return 1;
		}
		else
			seed = ok; 
	}
	srand(all * seed);
	char abc[26] = "aBcDeFgHiJkLmNoPqRsTuVwXyZ";
	char letter[7];
	int number[7];
	for(int i = 0; i < 7; i++) {
		letter[i] = abc[rand() % (sizeof(abc) - 1)];
		number[i] = rand() % 9;
		printf("%c%d", letter[i], number[i]);
	}

	return 0;
}
