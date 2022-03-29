#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Visitors[7];

void recordVisit(int n);
int factorialNoRec(int n);
int factorialRec(int n);

void main() {
	int num;
	printf("---Without Recursion---\n");
	printf("Please enter the number you want to get a factorial of:");
	scanf_s("%d", &num);
	int fact = factorialNoRec(num);
	printf("%d factorial with no recursion= %d", num, fact);
	printf("\n---With Recursion---\n");
	printf("Please enter the number you want to get a factorial of:");
	scanf_s("%d", &num);
	fact = factorialRec(num);
	printf("%d factorial with no recursion= %d", num, fact);
	recordVisit(7);
}

//Part 1
int factorialNoRec(int n){
	int Answer = 1;
	for (int i = 1; i <= n; i++) {
		Answer *= i;
	}
	return Answer;
}

//Part 2
int factorialRec(int n) {
	if (n==1) {
		return 1;
	}
	return n*factorialRec(n - 1);
}

void recordVisit(int n)
{
	int Visit;
	if (n >0) {
		printf("Enter the number of visitors:");
		scanf_s("%d", &Visit);
		Visitors[7-n] = Visit;
		recordVisit(n - 1);
	}
	else {
		printf("Daily visitors:\n");
		for (int i = 0; i < 7; i++) {
			printf("Day %d visitors = %d.\n", (i + 1), Visitors[i]);
		}
	}
}