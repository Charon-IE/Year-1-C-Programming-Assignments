#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <string.h>

void bubbleSort(int arrA[], int size);
void selectionSort(int arrA[], int size);
void insertionSort(int arrA[], int size);

#define SIZE 1000
void main() {

	int arrA[SIZE];		// array of integers 
	int i;
	FILE* infp;

	// read data in to array arrA[]
	fopen_s(&infp, "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\1000ints.txt", "r");
	if (NULL == infp) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}

	else {

		for (i = 0; fscanf_s(infp, "%d", &arrA[i]) == 1 && i < SIZE; i++);
	}

	fclose(infp);
	selectionSort(arrA, SIZE);
	//insertionSort(A, n);
	// bubbleSort(A, n);

	puts("Printing out Sorted array: ");
	for (int i = 0; i < SIZE; i++) {
		printf("\n %d", arrA[i]);
	}

	FILE* outfp;
	fopen_s(&outfp, "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\1000ints.txt", "w");

	if (outfp == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}
	else {
		for (i = 0; i < SIZE; i++) {
			fprintf(outfp, "%d\n", arrA[i]);
		}
	}
	fclose(outfp);


}

void bubbleSort(int arrA[], int size)
{
	int i, k, temp;

	for (k = 0; k < size; k++) {
		for (i = 0; i < size - 1 - k; i++) {
			if (arrA[i] > arrA[i + 1]) {
				//out of order so swap
				temp = arrA[i];
				arrA[i] = arrA[i + 1];
				arrA[i + 1] = temp;
			}
		} //end inner i for 
	} //end outer k for 
}

// Selection Sort: integer array arrA [] of size
void selectionSort(int arrA[], int size) {

	int i, j, min, temp;

	for (i = 0; i < size - 1; i++) {
		min = i;
		//find next smallest
		for (j = min + 1; j < size; j++) {
			if (arrA[min] > arrA[j]) {
				min = j;
			}
		}

		//swap values at locations i and min, if i != min
		if (i != min) {
			temp = arrA[i];
			arrA[i] = arrA[min];
			arrA[min] = temp;
		}
	} //end outer while
}


// Insertion Sort: integer array arrA [] of size
void insertionSort(int arrA[], int size)
{
	int i, j, curr;

	for (i = 1; i < size; i++) {
		curr = arrA[i];

		for (j = i - 1; j >= 0 && curr < arrA[j]; j--) {   //compare
			//make room ...
			arrA[j + 1] = arrA[j];
		}

		if (i != j + 1) // if not at the correct position already
			arrA[j + 1] = curr;

	} // end outer i for

}