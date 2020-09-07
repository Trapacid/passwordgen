// fixes error with clock_gettime
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <ctype.h>

#define BILLION 1000000000L

void GeneratePassword(int x, int y) {
	
	//char data[36] = "1aB2cD3eF4gH5iJ6kL7mN8oP9qR0sTuVwXyZ";
	char data[67] = "-abcdefghijklmnopqrstuvwxyz-!_ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-";
	char character[x];
	character[y] = data[rand() % (sizeof(data) - 1)];
	printf("%c", character[y - 1]);
	return;
}

int main(int argc, char **argv) {
	long int nanoseconds;
	uint64_t all;
	time_t seconds;
	struct timespec spec;
	
	clock_gettime(CLOCK_REALTIME, &spec);
	seconds = spec.tv_sec;
	nanoseconds = spec.tv_nsec;

	all = (uint64_t)seconds * BILLION + (uint64_t)nanoseconds;

	int len;
	uint32_t seed;
	if(argc <= 2) {
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

		printf("enter length: ");
		if(scanf("%d", &len) != 1 || len <= 3) {
			printf("enter a number that is greater than 3 for length");
			return 1;	
		}
	}
	else {
		int ok = atoi(argv[1]);
		len = atoi(argv[2]);
		if(ok == 0)
		{
			printf("enter a number that is not 0 or letters for seed\n");
			return 1;
		}
		else
			seed = ok; 
		if(len <= 3) {
			printf("enter a number greater than 3 for length");
			return 1;
		}
	}
	srand(all * seed);

	for(int i = 0; i <= len; i++) {
		GeneratePassword(len, i);
	}
//	printf("\0");
	return 0;
}
