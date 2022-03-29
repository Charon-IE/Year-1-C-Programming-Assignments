#include <stdio.h>
void main() {
    int ageOfChild = 0;
    int childNum;
    float sumOfAges = 0;
    float averageAges;
    int count = 0;
    int total;

    printf("Enter the ages of the children, one by one. Enter a negative number to exit \n");

    while (ageOfChild >= 0) {
        count++;
        printf("Enter the age of child %d: ", count);
        scanf_s("%d", &ageOfChild);

        sumOfAges = sumOfAges + ageOfChild;
    }
    printf("Exiting loop \n");

    count--;
    printf("There are %d children in the family \n", count);

    averageAges = sumOfAges / count;


    printf("The total age of the children is %0.1f years \n", sumOfAges);


}