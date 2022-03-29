
#include <string.h>
#include <stdio.h>

void displayConv();
float ozToLbs(float oz);
float lbsToKg(float lb);
float kgToTonnes(float kg);
void displayDelivery(int numBox, float boxW_kg, float costEurPKg);

void main() {
	displayConv();
	float prodW_oz = 300;
	int numProdPerBox = 50;
	int numBox = 20;
	float prodCostEurPerKG = 12.75;

	float prodW_lbs = ozToLbs(prodW_oz);

	float boxWeightKG = lbsToKg(prodW_lbs) * numProdPerBox;
	displayDelivery(numBox, boxWeightKG, prodCostEurPerKG);

}

void displayConv() {
	puts("16 oz in a pound.");
	puts("2.2 lbs in a kg.");
	puts("1000 kg in a tonne.");
}

float ozToLbs(float oz) {
	float lbs = oz / 16.0;
	return lbs;
}

float lbsToKg(float lb) {
	float kg = lb / 2.2;
	return kg;
}

float kgToTonnes(float kg) {
	float tonnes = kg / 1000.0;
	return tonnes;
}

void displayDelivery(int numBox, float boxW_kg, float costEurPKg) {
	float totWeightKG = numBox * boxW_kg;
	float totWeightTonnes = kgToTonnes(totWeightKG);
	float totCostEur = totWeightKG * costEurPKg;
	puts("++++++++++++++++++++");
	puts("Order summary");
	printf("%d boxes.\n", numBox);
	printf("Box weight is %0.2f Kg.\n", boxW_kg);
	printf("Total delivery weight is %0.2f Tonnes.\n", totWeightTonnes);
	printf("Total delivery cost is %0.2f Euro.\n", totCostEur);
}