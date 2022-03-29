#include <stdio.h>
void main() {
	float DaySales[1000];

	for (int i = 0; i < 7; i++) {
		printf("Enter the total sale (Euro) for Day %d : ", i + 1);
		scanf_s("%f", &DaySales[i]);
	}

	printf("Exited Loop: %f"), DaySales[4];
}