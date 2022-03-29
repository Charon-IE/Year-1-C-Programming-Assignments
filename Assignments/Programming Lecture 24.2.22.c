/*#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

int rnd(int lower, int upper);

int arr[10000];
int freq[101];

void main() {
	/*
	int Number = 0;
	printf("Pass a positive integer:");
	scanf_s("%d", &Number);
	int count = 0;
	int summation = 1;
	while (summation <= Number) {
		summation += 2;
		count++;
	}
	printf("Number of Terms Needed:%d", count);
	*/

	/*
	int Num;
	int Highest = 0;
	int HighestIndex = 0;
	srand(time(0));
	for (int i = 0; i < 10000; i++) {
		Num = rnd(0, 100);
		arr[i] = Num;
		freq[Num]++;
	}
	for (int i = 0; i < 102; i++) {
		if (freq[i] > Highest) {
			Highest = freq[i];
			HighestIndex = i;
		}
	}
	printf("%d occured most frequently is with a frequency of %d",HighestIndex, Highest);
	
	int Number = 0;
	int Count = 1;
	printf("Please enter a positive integer:");
	scanf_s("%d", &Number);

	for (int i = 1; i <= Number; i++) {
		while (Count<=i) {
			printf("*");
			Count++;
		}
		Count = 1;
		printf("\n");
	}
 }

int rnd(int lower, int upper) {
	int range = (upper - lower) + 1;
	return (rand() % range) + lower;
}
*/