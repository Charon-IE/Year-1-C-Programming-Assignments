#include <stdio.h>
void main() {
	int Age = 1, Max = 0, Min = 100;
	int i = 0;
	float TotalAge = 0;
	float Average;

	printf("If you want to continue, enter any number less than 0\n");

	while (Age >= 0) {
		i++;
		printf("Enter the age of the child %d: ", i);
		scanf_s("%d", &Age);
	}
}