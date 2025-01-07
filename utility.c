#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utility.h"

const int MAX_CHARS = 12;
const int SUPPORTED_BASES[] = {2,8,10,16};
const char SUPPORTED_CHARS[][17] = {"01","01234567", "0123456789", "0123456789ABCDEF"};
const char MATH_OPERATORS[4] = {'+','-','*','/'};

basenumber getNumberAndBase(int basesLength){
	// Maximum supported digits are 32 (+ \n from fgets and \0 char)
	char* input = malloc((MAX_CHARS + 2) * sizeof(char));
	basenumber inputUpper;
	inputUpper.value = malloc((MAX_CHARS + 2) * sizeof(char));
	bool compatibleLength, baseChecker;
	do {
		// Asks as input an integer
		printf("\nType an integer (Maximum supported digits %d): \t", MAX_CHARS);
		// Replaced gets(strArr) with fgets(strArr, maxChars, stdin) for security
		fgets(input, MAX_CHARS + 2, stdin);
		// Checks number of digits (2nd from the end char from fgets is \n)
		compatibleLength = (input[strlen(input) - 1] == '\n');
		if (!compatibleLength){
			clearInputBuffer();
			printf("\nUnsupported length of digits (max %d). Try again...\n", MAX_CHARS);
		}
	} while(!compatibleLength);
	do {
		// Gets from user and checks compatibility for current and new base of the number
		inputUpper.baseindex = validBase("current", basesLength);
		// Converts possible lowercase to capital before checking (lowerToUpper)
		inputUpper.value = lowerToUpper(input);
		// Adjust baseCheck to handle negative sign
		if (inputUpper.value[0] == '-') {
			baseChecker = baseCheck(inputUpper.baseindex, inputUpper.value + 1);
		} else {
			baseChecker = baseCheck(inputUpper.baseindex, inputUpper.value);
		}
		if (!baseChecker){
			printf("\nThe current base does not match with the number you typed. Try again...\n");
		}
	} while(!baseChecker);
	free(input);
	return inputUpper;
}


// Checks if an inserted base is supported by the program and returns SUPPORTED_BASE index
int validBase(char situation[], int iterationCounter){
	// Asks for the integer's base (checks if it's supported)
	int base, counter;
	bool isSupported = false;
	do {
		printf("\nType the %s base of the integer: \t", situation);
		scanf("%d", &base);
		clearInputBuffer();
		for(counter = 0; counter < iterationCounter; counter++){
			if(base == SUPPORTED_BASES[counter]){
				isSupported = true;
				break;
			}
		}		
	} while(isSupported == false);
	// Returns base according to the supported base map (check top of the program)
	return counter;
}

// Checks if the input is compatible to the base that the user gave
bool baseCheck(int base, char inputNumber[]){
	bool isValid;
	int inputChar, baseChar;
	int inputLength = strlen(inputNumber);
	int supportedCharsLength = strlen(SUPPORTED_CHARS[base]);
	for (inputChar = 0; inputChar < inputLength; inputChar++){
		// Resets character checker
		isValid = false;
		// Iterates each char of the input with each character supported by the declared base and checks for matching
		for(baseChar = 0; baseChar < supportedCharsLength; baseChar++){
			if (inputNumber[inputChar] == SUPPORTED_CHARS[base][baseChar]){
				isValid = true;
				break;
			}
		}
		// Exits if any character is invalid
		if(isValid == false){
			break;
		}
	}
	return isValid;	 	
}

char* lowerToUpper(char lowerString[]){
	int i;
	// Dynamic memory allocation
	char* upperString = malloc((strlen(lowerString) + 1) * sizeof(char));
	// Exits program in case of failed memory allocation
	if (upperString == NULL){
		printf("\nMemory allocation to lowerToUpper failed...");
		exit(2);
	}
	for (i = 0; lowerString[i] != '\0'; i++) {
		if(lowerString[i] >= 'a' && lowerString[i] <= 'z') {
				upperString[i] = lowerString[i] - 32;
		}
		else {
			upperString[i] = lowerString[i];
		}
	}
	// Replaces (\n) char that fgets adds by default in the end with (\0)
	upperString[strlen(lowerString) - 1] = '\0';
	return upperString;
}

// Clears the input buffer for scanf and fgets functions
void clearInputBuffer(void){
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}