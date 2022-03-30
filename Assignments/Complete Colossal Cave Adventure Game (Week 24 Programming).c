
//Declaring Libraries
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Struct for array of locations that are read from the file
typedef struct {
    char description[100];
    int n, s, e, w, in, out;
} location;

//Struct for array of object that are read from the file
typedef struct {
    char name[20];
    char description[100];
    int objectlocation;
} object;

//Enumeration that will be used with the switch statement, list of possible commands the user can enter
typedef enum {
    ERROR,
    N, S, E, W, IN, OUT,
    LOOK, HELP, TAKE, DROP,
    EXAMINE, INVENTORY, QUIT,
    END
} command;

//2-D string array that holds every command in the same order as the enumeration and switch statement
char commands[][20] = { "error","n","s","e","w","in","out","look","help","take", "drop", "examine", "inventory", "quit"};

//Declaring the locations array of type location struct to hold all the info about the location in its appropriate variable in the struct
location locations[40];
//Declaring the objects array of type object struct to hold all the info about the object in its appropriate variable in the struct
object objects[5];
int numLocations = 0;
int numObjects = 0;
//Declaring necessary file addresses for each file
char locationsFile[] = "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\adventure_locations.txt";
char objectsFile[] = "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\adventure_objects.txt";
//String to hold the name of the object the user enters
char OBJ[20] = "";
//Integer to hold the location of the player
int playerLocationNum = 1;
//Integer array to represent whether or not the player is carrying one of the 2 items. Element 0 = USB Drive, Element 1 = Ice Cream. 
//1 in either element represents that the player is carrying the item.
int Items[2] = {0,0};
//Temp array to hold lowercase version of the object's name read from the file
char TempLowerName[5][10];

//Function to open the file address
FILE* openFileForReading(char* filename) {
    FILE* file_ptr;
    fopen_s(&file_ptr, filename, "r");
    if (file_ptr == NULL)
        //If the file cant be opened, inform the user
        printf("Could not open %s\n", filename);
    return file_ptr;
}

//Function to convert a string fully into lowercase
void LowerCaseConverter(char String[]) {
    int i = 0;
    //Loop until string terminator is met
    while (String[i] != '\0') {
        //Convert each element to lowecase
        String[i] = tolower(String[i]);
        i++;
    }
}

//Boolean function to read in the locations from the file address
bool readLocations() {
    //Assign the return of the open function to the pointer
    FILE* file_ptr = openFileForReading(locationsFile);
    //If the file pointer cant be opened, return false
    if (file_ptr == NULL)
        return false;

    numLocations = 0;
    int readHeaderLines = 0;
    char line[200];
    //Keep looping until the end of the file is reached
    while (fgets(line, 99, file_ptr) != NULL) {
        //Skip the first two header lines of the file
        if (readHeaderLines < 2)
            readHeaderLines++;
        else {
            //Once header lines are skipped, begin scanning into the struct
            numLocations++;
            //l variable will represent the location struct
            location l;
            int locNum;
            //Scan each line in a certain format and attribute each scan to the variables in the structs
            sscanf_s(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%[^\t]\n", &locNum, &l.n, &l.s, &l.e, &l.w, &l.in, &l.out, l.description, 100);
            int len = (int)strlen(l.description);
            l.description[len - 1] = '\0'; // remove \n from the string
            if (l.description[len - 2] == '\r')
                l.description[len - 2] = '\0'; // also remove \r from the string
            locations[numLocations] = l; // the 1st location is 1 (not 0) so we can use 0 to mean 'nothing' in adventure_locations.txt

        }
    }
    //Once the while loop finishes, return true if successful 
    return true;
}

//Boolean function to read in object information and scan them into structs
bool readObjects() {
    FILE* file_ptr = openFileForReading(objectsFile);
    if (file_ptr == NULL)
        return false;
    //Num objects is set to -1 because we need the 0th element to represent the first object
    numObjects = -1;
    int readHeaderLines = 0;
    char line[200];
    //Keep looping until the end of the file is reached
    while (fgets(line, 99, file_ptr) != NULL) {
        //Skip the first two header lines of the file
        if (readHeaderLines < 2)
            readHeaderLines++;
        else {
            numObjects++;
            //o will represent the objects variable
            object o;
            //Scan each line in this format and assign each scan into those particular variables in the objects struct
            sscanf_s(line, "%[^\t]\t%d\t%[^\t]\n", o.name, 100, &o.objectlocation, o.description, 100);
            int len = (int)strlen(o.description);
            //Copy the name of the object into the temp 2-D string array 
            strcpy_s(TempLowerName[numObjects], 10, o.name);
            //Convert that word into lowercase, this will improve user experience and will make sure the user doesnt need to enter name of the object exactly as it was scanned in.
            //Each user input will be converted into lowercase too, so when the lowercase input and lowercase object name are compared, it will not longer consider the input wrong even if it was the correct object name
            //I.E (with the capitals in the right place). When asked for an object, the program will be able to understand the object if the input is full capitals or all lowercase when comparing.
            //The temp array perserves the original name (w/capitals) of the object which is printed throughout the program.
            LowerCaseConverter(TempLowerName[numObjects]);
            //If the description ends with a newline, remove it
            if (o.description[len - 1] == '\n') {
                o.description[len - 1] = '\0';
            }
            if (o.description[len - 2] == '\r')
                o.description[len - 2] = '\0'; // aslo remove \r from the string
            //Pass o into the array of objects
            objects[numObjects] = o;
        }
    }
    //Once the while loop finishes, return true if successful 
    return true;
}

//Command-type function used to understand the command entered by the user
command identifyCommand(char* txt) {
    //Loop through each member of the enumeration until end is reached
    for (int i = 0; i < (int)END; i++) {
           //If a match is found return the command 
        if (strcmp(txt, commands[i]) == 0)
            return (command)i;
    }
    //If it cant be found, return an error
    return ERROR;
}
//Boolean function to check if the user can move to that location
bool tryMoveTo(int locationNum) {
    //If the current locations attempt to move in a direction is not zero, set that location as the players current location and return true
    if (locationNum > 0 && locationNum <= numLocations) {
        playerLocationNum = locationNum;
        return true;
    }
    //If it is 0, inform the user they cant move in that direction
    printf("You can't go that way.\n");
    return false;
}

//Integer function used to check if the object is in that specific location
int isObject(int locationNum) {
    for (int i = 0; i < 2; i++) {
        //Loop through each object and compare the players current location to the objects location
        if (objects[i].objectlocation == locationNum) {
            //If there is a match, return 1
            return 1;
        }
    }
    //If not, return 0
    return 0;
}

//Function to check for the object that the user requested
int ExamineRequest(char* OBJ) {
    for (int i = 0; i < 2; i++) {
        //If there is a match between the object requested and if its currently in the location, return the objects id 
        if (strcmp(OBJ, TempLowerName[i]) == 0 && playerLocationNum == objects[i].objectlocation) {
            return i;
        }
    }
    //If not return -1, which means the object is not in the area
    return -1;
}

//Function for when the player takes an item
void TakeItem(int i) {
    //Set the appropriate item's element in the element to 1, which represents the fact that the player is carrying it
    Items[i] = 1;
    //Change the location of that item to 0, which means it wont appear in any of the locations
    objects[i].objectlocation = 0;
    //Inform the user that the item was taken successfully
    printf("%s was taken successfully!\n", objects[i].name);
}


int main() {
    //If both files were read in successfully start the game
    if (readLocations()&&readObjects()) {
        printf("Welcome to Galway Adventure. Type 'help' for help.\n");

        // game loop (one iteration per command from the player)
        //Intialize cmd command variable as error
        command cmd = ERROR;
        //Begin the loop with display location variable as true to print the location of the first location as you begin
        bool displayLocation = true;
        //Also print the objects in the location
        int displayObject = 0;
        //Integer to hold the result of the examinerequest function
        int ExamineReq;
        //Used to store the input of the command
        char txt[200] = "";

        //Continue looping until the user inputs quit
        while (cmd != QUIT) {
            //The currloc variable of type location gets all the info from the struct assigned to the player's current location
            location currLoc = locations[playerLocationNum];

            //If display location is true, print the description of the location and set it to false for the next iteration
            if (displayLocation) {
                printf("\n%s\n", currLoc.description);
                displayLocation = false; // (for next iteration)
            }
            else
                //If the location is not updated, do not display the items again
                displayObject = -1;

            //If displayobject is 1, show the items in the location
            if (displayObject == 1) {
                printf("Objects here: ");
                //Loop through each object and if there is a match between where the object currently is and the players location print the item to the screen
                for (int i = 0; i < 2; i++) {
                    if (objects[i].objectlocation == playerLocationNum) {
                        //If the item is in the location and the next one is too, print the items to the screen in a particular format
                        if (objects[i].objectlocation == playerLocationNum && objects[i+1].objectlocation == playerLocationNum) {
                            printf("%s, %s\n", objects[i].name, objects[i+1].name);
                            break;
                        }
                        //Else print out the single object
                        else
                        printf("%s\n", objects[i].name);
                    }
                }
                // Set display object to false (0) for the next iteration
                displayObject = 0;
            }
            //If there are no objects in the location, inform the user
            else if (displayObject == 0) {
                printf("Objects here: Nothing\n");
            }


            // read and interpret user input
            printf("> ");
            scanf_s("%s", txt, 10);
            //Change user's input to lowercase
            LowerCaseConverter(txt);
            //Send the lowercase txt to the identifycommand function
            cmd = identifyCommand(txt);

            //Swtich Statement
            switch (cmd) {
                // For each movement case, send the location the player is trying to move to the function and assign the results to the respective variables
                //Also check if there are any objects in the location they are trying to move to
            case N:
                displayLocation = tryMoveTo(currLoc.n);
                displayObject = isObject(currLoc.n);
                break;

            case S:
                displayLocation = tryMoveTo(currLoc.s);
                displayObject = isObject(currLoc.s);
                break;

            case E:
                displayLocation = tryMoveTo(currLoc.e);
                displayObject = isObject(currLoc.e);
                break;

            case W:
                displayLocation = tryMoveTo(currLoc.w);
                displayObject = isObject(currLoc.w);
                break;

            case IN:
                displayLocation = tryMoveTo(currLoc.in);
                displayObject = isObject(currLoc.in);
                break;

            case OUT:
                displayLocation = tryMoveTo(currLoc.out);
                displayObject = isObject(currLoc.out);
                break;

            case LOOK:
                //If the command is look, set display location to true and check if there objects in that location (in case user took an object)
                displayLocation = true;
                displayObject = isObject(playerLocationNum);
                break;

            case HELP:
                //Print each command if the user enters help
                printf("I know these commands:\n");
                for (int i = 1; i < (int)END; i++) {
                    if (i > 1)
                        printf(", ");
                    printf("%s", commands[i]);
                }
                printf(".\n");
                break;

            case EXAMINE:
                printf("Examine what?> ");
                //Scan input with space
                scanf_s(" %[^\n]s", OBJ, 20);
                //Convert string the lowercase
                LowerCaseConverter(OBJ);
                //Assign result of function to examinereq variable
                ExamineReq = ExamineRequest(OBJ);
                //If the function did not output a -1, print the description of the object thats in the area
                if (ExamineReq != -1) {
                    printf("%s\n", objects[ExamineReq].description);
                }
                //Else if, if the player is holding an item, check to see if it is the one they requested
                else if (Items[0] == 1 || Items[1] == 1) {
                    //For loop for the two items
                    for (int i = 0; i < 2; i++) {
                        //Compare the request again with a particular item
                        if (strcmp(OBJ, TempLowerName[i]) == 0) {
                            //AND if they have that exact item on their person, 0 = USB Drive, 1 = Ice Cream
                            if (Items[i] == 1) {
                                //Print the description
                                printf("%s\n", objects[i].description);
                            }
                        }
                    }
                }
                //If the request cant be matched with item at the location or the items they are carrying, inform the user that cant be examined
                else
                    printf("You can't examine that!\n");
                //Set displayobject to -1 so the objects arent printed again
                displayObject = -1;
                break;

            case TAKE:
                printf("Take what?> ");
                //Scan in with space
                scanf_s(" %[^\n]s", OBJ, 20);
                //Change the string to lowercase
                LowerCaseConverter(OBJ);
                //Send the string to the examinerequest function 
                ExamineReq = ExamineRequest(OBJ);
                //If the object is not in the location, inform the user they cant pick it up
                if (ExamineReq == -1) {
                    printf("You can't pick that up here!\n");
                }
                else
                    //If it is in the area send the id of the item into the takeitem function
                TakeItem(ExamineReq);
                //Set displayobject variable to -1 to avoid printing the items again next iteration
                displayObject = -1;
                break;

            case DROP:
                //If the player is carrying something, continue with drop protocall
                if (Items[0] == 1 || Items[1] == 1) {
                    printf("Drop what?> ");
                    //Scan input with space
                    scanf_s(" %[^\n]s", OBJ, 20);
                    //Change input to lowercase
                    LowerCaseConverter(OBJ);
                    for (int i = 0; i < 2; i++) {
                        //If the object requested matches with one of the items and the item is currently being carried
                        if (strcmp(OBJ, TempLowerName[i]) == 0 && Items[i] == 1) {
                            //Set that item as 0 (To mean its not being carried)
                            Items[i] = 0;
                            //Set the players location as the item's new location in the struct
                            objects[i].objectlocation = playerLocationNum;
                            //Inform the user it was successfully dropped
                            printf("Successfully dropped %s.\n", objects[i].name);
                        }
                    }
                }
                //If the requested item is not being carried or if theres an error, inform the user
                else {
                    printf("You are not carrying that!\n");
                }
                //Set display object to -1 to avoid printing the objects again next iteration
                displayObject = -1;
                break;

            case INVENTORY:
                //If the player has any items in his inventory
                if (Items[0] == 1 || Items[1] == 1) {
                    printf("You are carrying: ");
                    //Check to see what item the player is carrying
                    for (int i = 0; i < 2; i++) {
                        //If the player is carrying that specific item
                        if (Items[i] == 1) {
                            //If the loop is on its second iteration, and theres another match, print a comma to improve formatting
                            if (i == 1 && Items[0] == 1) {
                                printf(", ");
                            }
                            //Print the name of the item
                            printf("%s", objects[i].name);
                        }
                    }
                    printf("\n");
                }
                   //If the player isnt carrying anything, (i.e array's elements are both 0), inform the user
                else {
                    printf("You are not carrying anything!\n");
                }
                //Set to -1 to avoid printing items again next iteration
                displayObject = -1;
                break;

            case QUIT:
                //if player wants to exit, say bye and exit the while loop
                printf("Bye!\n");
                break;

            default:
                //If the command couldnt be understood, inform the user
                printf("Huh?\n");
                //And avoid printing objects again
                displayObject = -1;
            }
        }
    }
}
