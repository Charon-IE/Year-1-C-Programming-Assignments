//Name: Timonas Samoska
//Student ID: 21326923
//Date: 18/1/22 

//Libaries
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

//Global variables that represent the ship's x and y coordinates.
int shipX, shipY;
//Y is a global variable to ensure the co-ordinate of Y is remembered as the function reruns through recursion
int CurrY = -1;
//Global Variable to determine when recursion is no longer needed in the GridSearch function
int LocationFound = 0;

//Declaring Functions
void RandomSearch(int GridSize);
void GridSearch(int GridSize, int LocationsTried);

void main() {
	int GridSize = 10; 
	//Seeding the random generator with time
	srand(time(NULL));
	shipX = (rand() % GridSize);
	shipY = (rand() % GridSize);
	//Running Functions
	RandomSearch(GridSize);
	GridSearch(GridSize, 0);

	printf("\n=============New Grid=============\n");
	//Student ID Last Digit : 3
	GridSize = 3;
	//Generating new ship co-ordinates with student ID
	shipX = (rand() % GridSize);
	shipY = (rand() % GridSize);

	RandomSearch(GridSize);
	//Resetting Global Variables for Grid Search Function
	LocationFound = 0;
	CurrY = -1;
	GridSearch(GridSize, 0);
}

void RandomSearch(int GridSize) {
	int ShipFound = 0;
	int Counter = 0;
	int RandomX, RandomY = 0;
	//While loop to loop through randomly generated co-ordinates until ship is found
	while (ShipFound != 1) {
		//Attempt is incrased
		Counter++;
		//Random set of coordinates are generated
		RandomX = (rand() % GridSize);
		RandomY = (rand() % GridSize);
		//If random location generated equals the ship's location, exit the while loop
		if (RandomX == shipX && RandomY == shipY) {
			ShipFound = 1;
		}
	}
	printf("-----------Random Search----------\n");
	printf("Ship found after %d locations!\n", Counter);
	printf("Ship co-ordinates - x : %d, y : %d.\n", RandomX, RandomY);
}

void GridSearch(int GridSize, int LocationsTried) {
	//Current X variable is declared as -1 in the beginning of the while loop to ensure the co-ordinate 0 is included in the search
	int CurrX = -1;
	//If the location is not found run the following code 
	if (LocationFound!=1) {
		//The global variable is increased to search through each X co-ordinate for this value of Y in the function.
		CurrY++;

		//For this value of Y, a while function is used to run through each X value.
		while (CurrX <= GridSize-1 && LocationFound!=1) {
			CurrX++;
			//Attempts are increased as each X and Y value is checked 
			LocationsTried++;
			// If there is a match, the global variable is increased by 1 to escape the if statement and run the recursive function again.
			if (CurrX == shipX && CurrY == shipY) {
				LocationFound = 1;
			} 
		}

		 if (LocationFound == 0) {
			 //Attempt is decreased by one to ensure an accurate attempt value is kept through each rerun.
				LocationsTried--;
				//Recursive function
				GridSearch(GridSize, LocationsTried);
			}
		 //If the recursive function doesnt need to be rerun print the results.
		 else {
			 printf("-----------Grid Search------------\n");
			 printf("Ship found after %d locations!\n", LocationsTried);
			 printf("Ship co-ordinates - x : %d, y : %d.\n", CurrX, CurrY);
		 }
	}
}