
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

int randGroup(int numGroups);
int assignGroupProb(int group1Prob); // part 6
void displayProjectGroups(int g1[], int g2[], int g1Size, int g2Size);

void main() {

	srand(time(NULL));

	int project1emp[100];
	int project2emp[100];
	int numEmp = 80, numP1 = 0, numP2 = 0;

	int equalGroupNum = 0; // part 5, 0 = false(don't force equal groups), 1 = true (force equal groups). 

	for (int i = 0; i < numEmp; i++) {
		//int g = randGroup(2);
		int g = assignGroupProb(75); // part 5, 75% chance each employee in group 1
		if (g == 1) {
			project1emp[numP1] = i;
			numP1++;
		}
		else {
			project2emp[numP2] = i;
			numP2++;
		}
	}
	displayProjectGroups(project1emp, project2emp, numP1, numP2);

	// part 5 
	if (equalGroupNum) {
		printf("Ensuring equal group numbers\n");
		while (numP1 != numP2 && numEmp % 2 == 0) {
			if (numP1 > numP2) {
				project2emp[numP2] = project1emp[numP1 - 1];
				project1emp[numP1 - 1] = -1000;
				numP2++;
				numP1--;
			}
			else if (numP1 < numP2) {
				project1emp[numP1] = project2emp[numP2 - 1];
				project2emp[numP2 - 1] = -1000;
				numP1++;
				numP2--;
			}
		}
		displayProjectGroups(project1emp, project2emp, numP1, numP2);
	}

}


int randGroup(int numGroups) {
	int group = (rand() % numGroups) + 1;
	return group;
}

// part 6
int assignGroupProb(int group1Prob) {
	int r = rand() % 100;
	if (r < group1Prob) {
		return 1;
	}
	else {
		return 2;
	}
}

void displayProjectGroups(int g1[], int g2[], int g1Size, int g2Size) {
	printf("--- %d Project 1 employees----\n", g1Size);
	for (int i = 0; i < g1Size; i++) {
		printf("%d\n", g1[i]);
	}

	printf("---%d Project 2 employees----\n", g2Size);
	for (int i = 0; i < g2Size; i++) {
		printf("%d\n", g2[i]);
	}

}
