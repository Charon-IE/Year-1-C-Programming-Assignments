#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char description[100];
    int n, s, e, w, in, out;
} location;

typedef struct {
    char name[20];
    char description[100];
    int objectlocation;
} object;

typedef enum {
    ERROR,
    N, S, E, W, IN, OUT,
    LOOK, HELP, TAKE, DROP,
    EXAMINE, INVENTORY, QUIT,
    END
} command;

char commands[][20] = { "error","n","s","e","w","in","out","look","help","take", "drop", "examine", "inventory", "end"};

location locations[40];
object objects[5];
int numLocations = 0;
int numObjects = 0;
char locationsFile[] = "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\adventure_locations.txt";
char objectsFile[] = "C:\\Users\\burli\\OneDrive - National University of Ireland, Galway\\Desktop\\adventure_objects.txt";
char OBJ[20] = "";
int playerLocationNum = 1;
int Items[2] = {0,0};

FILE* openFileForReading(char* filename) {
    FILE* file_ptr;
    fopen_s(&file_ptr, filename, "r");
    if (file_ptr == NULL)
        printf("Could not open %s\n", filename);
    return file_ptr;
}

bool readLocations() {
    FILE* file_ptr = openFileForReading(locationsFile);
    if (file_ptr == NULL)
        return false;

    numLocations = 0;
    int readHeaderLines = 0;
    char line[200];
    while (fgets(line, 99, file_ptr) != NULL) {
        if (readHeaderLines < 2)
            readHeaderLines++;
        else {
            numLocations++;
            location l;
            int locNum;
            sscanf_s(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%[^\t]\n", &locNum, &l.n, &l.s, &l.e, &l.w, &l.in, &l.out, l.description, 100);
            int len = (int)strlen(l.description);
            l.description[len - 1] = '\0'; // remove \n from the string
            if (l.description[len - 2] == '\r')
                l.description[len - 2] = '\0'; // aslo remove \r from the string
            locations[numLocations] = l; // the 1st location is 1 (not 0) so we can use 0 to mean 'nothing' in adventure_locations.txt

        }
    }

    return true;
}

bool readObjects() {
    FILE* file_ptr = openFileForReading(objectsFile);
    if (file_ptr == NULL)
        return false;

    numObjects = -1;
    int readHeaderLines = 0;
    char line[200];
    while (fgets(line, 99, file_ptr) != NULL) {
        if (readHeaderLines < 2)
            readHeaderLines++;
        else {
            numObjects++;
            object o;
            sscanf_s(line, "%[^\t]\t%d\t%[^\t]\n", o.name, 100, &o.objectlocation, o.description, 100);
            int len = (int)strlen(o.description);
            o.description[len - 1] = '\0'; // remove \n from the string
            if (o.description[len - 2] == '\r')
                o.description[len - 2] = '\0'; // aslo remove \r from the string
            objects[numObjects] = o;
        }
    }

    return true;
}

command identifyCommand(char* txt) {
    for (int i = 0; i < (int)END; i++) {
        if (strcmp(txt, commands[i]) == 0)
            return (command)i;
    }
    return ERROR;
}

bool tryMoveTo(int locationNum) {
    if (locationNum > 0 && locationNum <= numLocations) {
        playerLocationNum = locationNum;
        return true;
    }

    printf("\nYou can't go that way.\n\n");
    return false;
}

int isObject(int locationNum) {
    for (int i = 0; i < 2; i++) {
        if (objects[i].objectlocation == locationNum) {
            return 1;
        }
    }
    return 0;
}

int ExamineObject(char* OBJ) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(OBJ, objects[i].name) == 0 && playerLocationNum == objects[i].objectlocation) {
            return i;
        }
    }
    return -1;
}

void itemManagement(int i) {
    Items[i] = 1;
    objects[i].objectlocation = 0;
    printf("%s was taken successfully!\n", objects[i].name);
}

int main() {
    if (readLocations()&&readObjects()) {
        printf("Welcome to Galway Adventure. Type 'help' for help.\n");

        // game loop (one iteration per command from the player)
        char txt[200] = "";
        command cmd = ERROR;
        bool displayLocation = true;
        int displayObject = 0;
        int ExamineReq;

        while (cmd != QUIT) {
            location currLoc = locations[playerLocationNum];

            if (displayLocation) {
                printf("\n%s\n", currLoc.description);
                displayLocation = false; // (for next iteration)
            }

            if (displayObject == 1) {
                printf("Objects here: ");
                for (int i = 0; i < 2; i++) {
                    if (objects[i].objectlocation == playerLocationNum) {
                        printf("%s\n", objects[i].name);
                    }
                }
                displayObject = 0;
            }

            else if (displayObject == 0) {
                printf("Objects here: Nothing\n");
            }


            // read and interpret user input
            printf("> ");
            scanf_s("%s", txt, 10);
            cmd = identifyCommand(txt);

            switch (cmd) {
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
                displayLocation = true;
                break;

            case HELP:
                printf("I know these commands:\n");
                for (int i = 1; i < (int)END; i++) {
                    if (i > 1)
                        printf(", ");
                    printf("%s", commands[i]);
                }
                printf(".\n\n");
                break;

            case EXAMINE:
                printf("Examine what?> ");
                scanf_s(" %[^\n]s", OBJ, 20);
                ExamineReq = ExamineObject(OBJ);
                if (ExamineReq != -1) {
                    printf("%s\n", objects[ExamineReq].description);
                }
                else if (Items[0] != 0 && Items[1] != 0) {
                    for (int i = 0; i < 2; i++) {
                        if (strcmp(OBJ, objects[i].name) == 0) {
                            if (Items[i] == 1) {
                                printf("%s\n", objects[i].description);
                            }
                        }
                    }
                }
                else
                    printf("Theres nothing to examine\n");

                displayObject = -1;
                break;

            case TAKE:
                printf("Take what?> ");
                scanf_s(" %[^\n]s", OBJ, 20);
                ExamineReq = ExamineObject(OBJ);
                if (ExamineReq == -1) {
                    printf("You can't pick that up here!\n");
                }
                else
                itemManagement(ExamineReq);
                displayObject = -1;
                break;

            case QUIT:
                printf("Bye!\n");
                break;

            default:
                printf("Huh?\n");
            }
        }
    }
}