#include <stdio.h>
#include <string.h>
void main() {
	char Joe[50] = { 0 };

	printf("Jacks PC........... HACK100 GREAT SUCCESS: ");
	scanf_s("%49s", Joe, 50);
	printf("%s", Joe);

	if (strcmp(Joe,"Greg") == 0) {

		printf("Joe");
	}
 }