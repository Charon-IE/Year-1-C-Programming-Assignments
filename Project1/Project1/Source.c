
#include <stdio.h>
void main()
{
	int grade = 0;

	printf("Enter grade:");
	scanf_s("%d", &grade);

	if (grade >= 60)
	{
		printf("Passed \n");
	}
	else
	{
		printf("Failed \n");
	}
}