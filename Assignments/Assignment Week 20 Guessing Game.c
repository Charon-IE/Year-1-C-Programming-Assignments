/*
//Name: Timonas Samoska
//Student ID: 21326923
//Date: 1/3/22 

//Declaring Libraries
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Declaring Function Parameters
int ReadInDictionary();
int RandomWord(int Lower, int Upper);
int Game(int Word);

//Declaring 2-D dictionary character array as a heap. 100000 words with 200 character size each.
char Dictionary[100000][200];


void main() {
	//time function returns seconds since Jan 1 1970. Stored in a unsigned int variable
	 unsigned int lt = (unsigned int) time(NULL);
	//rnd() function is seeded with number of seconds since Jan 1 1970
	srand(lt);
	//Words stores number of compatible words returned from the ReadInDictionary function
	int Words = ReadInDictionary();
	//If the file pointer couldnt be read, close the program
	if (Words == 0) {
		printf("Error reading file pointer");
	}
	else {
		printf("Loaded %d suitable words from the Dictionary", Words);
		//Random index of a word is returned. 0 and number of suitable words are passed into the function to find the range of possible words
		int IndexWordPicked = RandomWord(0, Words);
		//Random word index is passed into the guessing game function
		int Guesses = Game(IndexWordPicked);
		printf("Well done, that took you %d guesses to find %s", Guesses, &Dictionary[IndexWordPicked]);
	}
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
			//If word doesnt meet requirements, don't paste it into the array and continue the loop
			if (length > 7 || length < 4) {
				continue;
			}
			else {
				//If the word meets the requirements, paste the word into the dictionary, length is increased by one each time to ensure the null character is also pasted.
				//strlen does not include the null character in the value that is returned
				strcpy_s(Dictionary[i], (length + 1), First);
				//I is incremented to ensure the next word is pasted into the right index of the character array
				i++;
		}
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

int RandomWord(int lower, int upper) {
	//Range is calculated by taking away the upper and lower number and adding 1 to include 0.
	int range = (upper - lower) + 1;
	//Modulus of the rand() function is used to generate a random number in the required range
	return (rand() % range) + lower;
}

int Game(int Word) {
	//All the variables required are declared
	//Counter is initialized to 1 because the while loop begins once the while loop begins
	int Counter = 1;
	//Empty character
	char Letter = '\0';
	//Length of the random word is found and assigned to the length variable
	int	Length = (int)strlen(Dictionary[Word]);
	//GuessedWords array is used to store each letter that the user guesses correctly
	char GuessedWords[7] = { 0 };
	//Counter for number of right words guesses is stored in this variable
	int GuessedTotalRightWords = 0;

	printf("\nGuess 1.\n");
	//For the first guess, underscores are printed for the number of letter in the random word
	for (int o = 0; o < Length; o++) {
		printf("_ ");
	}

	//While loop will loop for the duration of the game until the total number of guessed words is greater or equal to the length of the random word
	while (GuessedTotalRightWords < Length) {
		printf("\n");
		printf("\nGuess a letter>");
		scanf_s(" %c", &Letter, 1);

		//If the word is a digit, scan again until the entered word is no longer a digit
		while (isdigit(Letter)) {
			printf("\nThat is not a letter, try again.");
			printf("\nGuess a letter>");
			scanf_s(" %c", &Letter, 1);
		}

		//Entered letter is turned to lowercase 
		Letter = tolower(Letter);
		//Counter is incremented to ensure the guess number is kept up to date
		Counter++;

		//First for loop is used to check how many letters have been guessed correctly so far
		for (int j = 0; j < Length; j++) {
			//If the letter inputted matches one of the words in the word and the slot in the guessed words character array is empty then add that letter to the array at the position
			if (Letter == Dictionary[Word][j] && GuessedWords[j] == '\0') {
				GuessedWords[j] = Letter;
				//GuessedTotaRightlWords is incremented
				GuessedTotalRightWords++;
			}
			//If the guessedtotalrightwords variable is the same as the length, break from the while loop and finish the game
			else if (GuessedTotalRightWords == Length) {
				break;
			}
		}
		//If the guessedtotalrightwords variable is less than the length of the random word length the print out the underscores and words guessed so far
		if (GuessedTotalRightWords < Length) {
			printf("Guess %d.\n", Counter);
			//Second for loop to loop through each word
			for (int u = 0; u < Length; u++) {
				//If the character at the u position is not empty, print the letter
					if (GuessedWords[u] != '\0') {
						printf("%c ", GuessedWords[u]);
					}
					//And if it is empty, print an underscore
					else {
						printf("_ ");
					}
			}
		}
	}
	//Once while loop finishes, return the number of guesses minus 1 as it was initialized to 1 in the beginning.
		return Counter - 1;
	}
	*/