#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen, strcpy
#include <math.h> // pow

int validBase(char situation[], int iterationCounter);
int baseCheck(int base, char inputNumber[]);
char* lowerToUpper(char lowerString[]);
char* baseConverter(int base, int newBase, char inputNumber[]);
char* convertToDecimal(int base, char inputNumber[]);
char* convertFromDecimal(int base, char inputNumber[]);

/*
	Supported bases map (useful for the 2 arrays below and validBase function) 
	0 = BASE 2
	1 = BASE 10
	2 = BASE 16
*/

const int MAX_CHARS = 48;
const int SUPPORTED_BASES[] = {2,10,16};
const char SUPPORTED_CHARS[][17] = {"01", "0123456789", "0123456789ABCDEF"};

int main(int argc, char *argv[]) {
	// Maximum supported digits are 48
	char input[MAX_CHARS];
	int supportedLength, baseChecker, currentBase, nextBase;
	// Asks as input an integer
	printf("Type an integer (Maximum supported digits 48): \n");
	// Replaced gets(strArr) with fgets(strArr, maxChars, stdin) for security
	fgets(input, sizeof(input), stdin);
	// Number of supported bases that will be used as iteration counter
	supportedLength = sizeof(SUPPORTED_BASES)/sizeof(SUPPORTED_BASES[0]);
	// Gets from user and checks compatibility for current and new base of the number
	currentBase = validBase("current", supportedLength);
	// Converts possible lowercase to capital before checking (lowerToUpper)
	char* inputUpper = lowerToUpper(input);
	baseChecker = baseCheck(currentBase, inputUpper);
	if (baseChecker == 0){
		printf("The current base does not match with the number you typed. Try again...\n");
		free(inputUpper);
		return 1;
	}
	nextBase = validBase("next", supportedLength);
	char* result = baseConverter(currentBase, nextBase, inputUpper);
	printf("Number before conversion (base %d):\t%s\nNumber after conversion (base %d):\t%s\n", SUPPORTED_BASES[currentBase], inputUpper, SUPPORTED_BASES[nextBase], result);
	// result and inputUpper is identical, so only one free is required (see baseConverter)
	free(inputUpper);
	// Avoids double free in case of same current and next base
	if (currentBase != nextBase){
		free(result); 
	}
	return 0;
}


// Checks if an inserted base is supported by the program
int validBase(char situation[], int iterationCounter){
	// Asks for the integer's base (checks if it's supported)
	int base, counter, isSupported = 0;
	do {
		printf("Type the %s base of the integer: \n", situation);
		scanf("%d", &base);
		for(counter = 0; counter < iterationCounter; counter++){
			if(base == SUPPORTED_BASES[counter]){
				isSupported = 1;
				break;
			}
		}		
	} while(isSupported == 0);
	// Returns base according to the supported base map (check top of the program)
	return counter;
}

// Checks if the input is compatible to the base that the user gave
int baseCheck(int base, char inputNumber[]){
	int isValid, inputChar, baseChar;
	int inputLength = strlen(inputNumber);
	int supportedCharsLength = strlen(SUPPORTED_CHARS[base]);
	for (inputChar = 0; inputChar < inputLength; inputChar++){
		// Resets character checker
		isValid = 0;
		// Iterates each char of the input with each character supported by the declared base and checks for matching
		for(baseChar = 0; baseChar < supportedCharsLength; baseChar++){
			if (inputNumber[inputChar] == SUPPORTED_CHARS[base][baseChar]){
				isValid = 1;
				break;
			}
		}
		// Exits if any character is invalid
		if(isValid == 0){
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
		printf("Memory allocation to lowerToUpper failed...\n");
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


char* baseConverter(int base, int newBase, char inputNumber[]){
	if (base == newBase){
		return inputNumber;
	}
	else if (base == 1){
		return convertFromDecimal(newBase, inputNumber);
	}
	else {
		char toDecimal[MAX_CHARS];
		// Uses base 10 as middle converter
		strcpy(toDecimal, convertToDecimal(base, inputNumber));
		return convertFromDecimal(newBase, toDecimal);
	}
}

char* convertToDecimal(int base, char inputNumber[]){
	int i, resultInteger = 0;
	char* resultString = malloc(MAX_CHARS * sizeof(char));
	if(resultString == NULL){
		printf("Memory allocation to convertToDecimal failed\n");
		exit(3);
	}
	for (i = 0; i < strlen(inputNumber); i++){
		switch(inputNumber[i]){
			case 'A':
				resultInteger += 10 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			case 'B':
				resultInteger += 11 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			case 'C':
				resultInteger += 12 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			case 'D':
				resultInteger += 13 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			case 'E':
				resultInteger += 14 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			case 'F':
				resultInteger += 15 * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
			default:
				// Converts char to int according to its position in the ASCII table
				resultInteger += (inputNumber[i] - 48) * pow(SUPPORTED_BASES[base],strlen(inputNumber) - 1 - i);
			break;
		}
	}
	// Converts the integer (from resultInteger) to string and stores it to resultString 
	sprintf(resultString, "%d", resultInteger);
	return resultString;
}

char* convertFromDecimal(int base, char inputNumber[]){
	int inputInt = atoi(inputNumber), digitRemainder[MAX_CHARS], digitCounter, j;
	char* charRemainder = malloc(MAX_CHARS * sizeof(char));
	char* outputString = malloc (MAX_CHARS * sizeof(char));
	if (charRemainder == NULL || outputString == NULL){
		printf("Memory allocation to convertFromDecimal failed\n");
		exit(4);
	}
	for (digitCounter = 0; inputInt != 0; digitCounter++){
		digitRemainder[digitCounter] = inputInt % SUPPORTED_BASES[base];
		inputInt = inputInt / SUPPORTED_BASES[base];
		switch(digitRemainder[digitCounter]){
			case 10:
				charRemainder[digitCounter] = 'A';
			break;
			case 11:
				charRemainder[digitCounter] = 'B';
			break;
			case 12:
				charRemainder[digitCounter] = 'C';
			break;
			case 13:
				charRemainder[digitCounter] = 'D';
			break;
			case 14:
				charRemainder[digitCounter] = 'E';
			break;
			case 15:
				charRemainder[digitCounter] = 'F';
			break;
			default:
				charRemainder[digitCounter] = (char)(digitRemainder[digitCounter] + 48);
			break;
		}
	}
	for (j = 0; j < digitCounter; j++){
		outputString[j] = charRemainder[digitCounter - 1 - j];
	}
	// Explicitly ends the string to avoid printing junk chars
	outputString[digitCounter] = '\0';
	free(charRemainder);
	return outputString;
}