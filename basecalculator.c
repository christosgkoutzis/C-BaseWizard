#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "basecalculator.h"
#include "baseconverter.h"
#include "utility.h"


basenumber baseCalculator(basenumber number1, int basesLength){
	basenumber number2 = getNumberAndBase(basesLength), calcResult;
	// Initializing the strings in NULL prevents unnecessary memory allocation
	char* number1ToDec = NULL;
	char* number2ToDec = NULL;
	long long number1Int, number2Int; 
	int base10counter;
	float resultFlo;
	calcResult.value = malloc((MAX_CHARS + 2) * sizeof(char));
	char operator = validMathOperator();
	// Converts both string numbers to base10 format
	if (SUPPORTED_BASES[number1.baseindex] != 10){
		number1ToDec = convertToDecimal(number1.baseindex, number1.value);
	} else {
		number1ToDec = number1.value;
	}
	if (SUPPORTED_BASES[number2.baseindex] != 10){
		number2ToDec = convertToDecimal(number2.baseindex, number2.value);
	} else {
		number2ToDec = number2.value;
	}
	// Converts to integers the base 2 numbers
	number1Int = strtoll(number1ToDec, NULL, 10);
	number2Int = strtoll(number2ToDec, NULL, 10);
	// Performs the base10 operation regarding the operator's input
	switch(operator){
		case '+':
			resultFlo = (float)(number1Int + number2Int);
		break;
		case '-':
			switchPositions(&number1Int, &number2Int);
			resultFlo = (float)(number1Int - number2Int);
		break;
		case '*':
			resultFlo = (float)(number1Int * number2Int);
		break;
		case '/':
			switchPositions(&number1Int, &number2Int);
			if(number2Int == 0){
				printf("Calculation is impossible. Exiting program...");
				exit(6);
			}
			resultFlo = (float)number1Int / (float)number2Int;
			break;
	}
	// Copies as a string the float value of the number to calcResult
	sprintf(calcResult.value,"%.2f",resultFlo);
	checkValidResultDigits(calcResult.value);
	// Fills baseindex with base10 counter
	for (base10counter = 0; base10counter < basesLength; base10counter++){
		if(SUPPORTED_BASES[base10counter] == 10){
			break;
		}
	}
	calcResult.baseindex = base10counter;
	int convertInput = 0;
	bool isValidInput;
	printf("\n-------- | Integer Base Calculator Results | ------- \n\nOperation:\t%s (base %d) %c %s (base %d) = %s (base 10)\n", number1.value, SUPPORTED_BASES[number1.baseindex], operator, number2.value, SUPPORTED_BASES[number2.baseindex], calcResult.value);
	do {
		printf("\nDo you want to convert it to another base (only the integer part will be converted for divisions)?(press 0 for no or 1 for yes)\n\nAnswer:\t");
		scanf("%d", &convertInput);
		clearInputBuffer();
		isValidInput = (convertInput == 0 || convertInput == 1);
		if (!isValidInput){
			printf("\nIncorrect input. Please try again...");
		}
	} while (!isValidInput);
	if (convertInput == true) {
		calcResult.baseindex = validBase("next", basesLength);
		strcpy(calcResult.value, convertFromDecimal(calcResult.baseindex, strtok(calcResult.value, ".")));
		printf("\nNew integer value: \t%s\nNew Base: \t%d", calcResult.value, SUPPORTED_BASES[calcResult.baseindex]);
	}
	free(number2.value);
	if (SUPPORTED_BASES[number1.baseindex] != 10) {
		free(number1ToDec);
	}
	if (SUPPORTED_BASES[number2.baseindex] != 10) {
		free(number2ToDec);
	}
	return calcResult;
}

// Checks if the input is a valid math operator
char validMathOperator(void){
	int i;
	char mathOperator;
	bool isValidOperator = false;
	do {
	printf("\nType an operator(+,-,*,/):\t");
	scanf("%c", &mathOperator);
	clearInputBuffer();
	for(i = 0; i < 4; i++){
		if(MATH_OPERATORS[i] == mathOperator){
			isValidOperator = true;
		}
	}
	if (!isValidOperator){
		printf("\nIncorrect operator input. Try again...");
	}
	} while(!isValidOperator);
	return mathOperator;
}

// Switches the positions of 2 integers (using pointers)
void switchPositions(long long *number1, long long *number2){
	int switchSelect;
	bool isValidInput;
	do{
		printf("\nThe current position before the operation is:\n\tNumber 1:\t%lld\n\tNumber 2: \t%lld\nDo you want to switch positions(press 0 for no and 1 for yes)?\t", *number1, *number2);
		scanf("%d", &switchSelect);
		clearInputBuffer();
		isValidInput = (switchSelect == 0 || switchSelect == 1);
		if (!isValidInput){
			printf("\nIncorrect input. Please try again...");
		}
	} while (!isValidInput);
	if(switchSelect){
		int temp = *number1;
		*number1 = *number2;
		*number2 = temp;
	}
	return;
}