/*
//Name: Timonas Samoska
//Student ID: 21326923
//Date: 9/3/22 

//Declaring Libraries
#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Declaring global arrays
char SeparatedWords[200][30];
char StrippedText[200000];
char alltext[200000];
char oneline[1000];

//Setting function parameters
int CountWords();
int CountSyllables(int numWords);
void StripText();
int CountSentences();
float FleschReadabilityIndex(int Syllables, int Words, int Sentences);


int main() {
    //File pointer declared
    FILE* file_ptr;

    fopen_s(&file_ptr, "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\article-irish-times.txt", "r"); // open for reading

    if (file_ptr == NULL) {
        printf("Could not open article\n");
    }
    else {
        alltext[0] = '\0'; // make sure this string is empty
        while (fgets(oneline, 999, file_ptr) != NULL) {
            // read the next line and append it (with \n intact)
            //All the text from the file is now in the alltext array
            strcat_s(alltext, 999,oneline);
        }
      puts("The following paragraph has been extracted from the file:\n");
      printf("%s\n", alltext);

        fclose(file_ptr);
    }
    //Text is stripped of all punctuation using the strip text function to ensure only the words with no punctuation are copied into the strippedwords array
    //This will ensure there are no bugs when counting syllables or words
    StripText();
    //Number of words returned from the function are assigned to the numwords variable
    int numWords = CountWords();
    //Number of words is printed
    printf("\nWord Count:%d\n", numWords);
    //Number of syllables returned from the function are assigned to the numsyllables variable
    int numSyllables = CountSyllables(numWords);
    printf("Syllable Count: %d\n", numSyllables);
    //Number of sentences returned from the function are assigned to the numsentences variable
    int numSentences = CountSentences();
    printf("Number of Sentences: %d\n", numSentences);
    //Flesch Index returned from the function is assigned to the Index variable
    float Index = FleschReadabilityIndex(numSyllables, numWords, numSentences);
    printf("\nFlesch Readability Index: %f\n", Index);
}

int CountWords() {
    //Delimiter is set as a space and new line
    const char delimiter[] = " \n";
    //Token is empty
    char* Token = "\0";
    char* Next = NULL;
    int WordCount = 0;

    //First, token gets the word before the first space in the text
    Token = strtok_s(StrippedText, delimiter, &Next);
    //If the token is not empty continue running the while loop
    while (Token != NULL) {
        //Copy the token into the 2D array for each word. Each word in the text will be separated
        strcpy_s(SeparatedWords[WordCount], 20, Token);
        //Increase word counter to keep track of how many words are present in the text
        WordCount++;
        //Get the next token from the next delimiter
        Token = strtok_s(NULL, delimiter, &Next);
    }
    //Return the word count plus one in order to ensure the word outside the while loop is included
    return WordCount + 1;
}

int CountSyllables(int numWords) {
    //Begin by reducing the numwords parameter by 1 in order for the for loop to loop the right amount of times
    numWords--;
    int length = 0;
    int Syllables = 0;
    int Total = 0;
    //For loop to loop through every word in the 2D array
    for (int i = 0; i < numWords; i++) {
        //Length of the word is retrieved and used in the next for loop
        length = (int)strlen(SeparatedWords[i]);
        //This for loop will loop through every letter of each word in the 2D array
        for (int u = 0; u < length; u++) {
            //strchr is used to compare every vowel to each letter of each word. To lower is used to ensure no capitals are present
            if (strchr("aeiouy", tolower(SeparatedWords[i][u])) != NULL) {
                //If the word is a vowel, ensure it isnt an e at the end of the word. If it isnt, increase the syllables counter.
                if (strchr("e",tolower(SeparatedWords[i][length - 1])) == NULL) {
                    Syllables++;
                }
                //If the next letter of vowel is another vowel, do not increase the syllables counter and skip the next letter in the loop
                if (strchr("aeiouy", tolower(SeparatedWords[i][u+1])) != NULL) {
                    u++;
                }
            }
        }
        //If a word has no syllables at the end of the letter loop, set syllables to 1 as each word has atleast one syllable
        if (Syllables == 0) {
          Syllables = 1;
        }
        //Add syllables counter to the running total and reset the syllables counter back to 0
        Total += Syllables;
        Syllables = 0;
    }
    //Return total back to main
    return Total;
}

void StripText() {
    //Copy the alltext array to the stripped text array
    for (int i = 0; i < strlen(alltext); i++) {
        StrippedText[i] = alltext[i];
    }
    //Loop through the stripped text array and use strchr to look for any punctuation evident in the text.
    for (int i = 0; i < strlen(StrippedText); i++) {
        if (strchr(".\",", StrippedText[i]) != NULL) {
            //If punctuation is evident, move the entire array to the left, essentially removing the punctuation character from the array and overwriting it
            for (int t = i; t < strlen(StrippedText); t++) {
                StrippedText[t] = StrippedText[t + 1];
            }
            //Reduce I by one as there is one less element in the array
            i--;
        }
    }
}

int CountSentences() {
    int numSentences = 0;
    //Loop through the alltext array
    for (int i = 0; i < strlen(alltext); i++) {
        //If a certain type of punctuation is evident, increase the sentence counter
        if (strchr(".:;?!", alltext[i]) != NULL) {
            numSentences++;
        }
        else {
            //Else continue looping
            continue;
        }
    }
    //Return the number of sentences back to main
    return numSentences;
}

float FleschReadabilityIndex(int Syllables, int Words, int Sentences) {
    float Index;
    //Formula for the flesch readability index is calculated using the num of syllables, words and sentences that were fed into the function
    Index = (float)(206.835 - (84.6*(Syllables / Words)) - (1.015*(Words / Sentences)));
    //Index calculated is return to main
    return Index;
}
*/