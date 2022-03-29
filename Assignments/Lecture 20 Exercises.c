

/*
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char Dictionary[100000][200];


int ReadInDictionary();
void SpellChecker();

void main() {
	SpellChecker();
}

int ReadInDictionary() {
	FILE* fptr;
	//Delimiter used is newline for strtok function
	char Delimiter[] = "\n";
	char line[200];
	int i = 0;
	size_t length;
	fopen_s(&fptr, "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\dictionary.txt", "r");
	//If there is no error with the file pointer, find the length of the file
	if (fptr != NULL) {
		//While the pointer hasnt reached the end of the file, run the while loop till the end of the file is reached
		while (!feof(fptr)) {
			//Paste entire current line the pointer is on into line character array
			fgets(line, 200, fptr);
			//Variables used to store the strings are declared
			char* Next = NULL;
			//strtok is used to parse the entire line until the delimiter is reached
			char* First = strtok_s(line, Delimiter, &Next);
			//The length of the word parsed is checked in order to reject words that are less than 4 or more than 7 words long
				length = strlen(First);
				strcpy_s(Dictionary[i], (length + 1), First);
				//I is incremented to ensure the next word is pasted into the right index of the character array
				i++;
		}
		fclose(fptr);
		//Return i (number of suitable words that were pasted into the dictionary character array)
		return i;
	}
	//If there is an error with the file pointer, return 0 (Ensures all possibilites are covered and something is returned in each scenario)
	else {
		return 0;
	}
}

void SpellChecker() {
	char Word[50] = { 0 };
	int Result = 0;
	int Return = ReadInDictionary();
	printf("Spellchecking Exercise\n");
	printf("Loaded %d words from the dictionary.\n", Return);
	printf("Please enter a word:");
	scanf_s("%s", Word, 20);
	int Length = (int)strlen(Word);
	int CorrectCharacter = 0;
	for (int i = 0; i < Return; i++) {
		for (int u = 0; u < Length; u++) {
			if (Dictionary[i][u] == tolower(Word[u])) {
				CorrectCharacter++;
			}
			else {
				break;
			}
		}
		if (CorrectCharacter == Length) {
			Result = i + 1;
			break;
		}
		else {
			CorrectCharacter = 0;
			Result = i + 1;
			continue;
		}
	}
	if (CorrectCharacter == Length) {
		printf("%s is in the dictionary, taking %d number of tests", Word, Result);
	}
	else {
		printf("%s is not in the dictionary, taking %d number of tests", Word, Result);
	}
}
*/