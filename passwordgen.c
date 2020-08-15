#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	unsigned seed;
	if(argc <= 1) {
		printf("input seed: ");
		int how;
		if(scanf("%d", &how) == 1)
			seed = how;
		else
			printf("enter a number fr2\n");
	}
	else {
		int ok = atoi(argv[1]);
		seed = ok; 
	}
	srand(time(0) * seed);
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
