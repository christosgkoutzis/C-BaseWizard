#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //bool (data type), true-false (keywords)
#include <string.h> //strlen, strcpy
#include <math.h> //pow

#define toolLength 2
/*
	Supported tools map
	1 = Integer Base Converter
	2 = Integer Base Calculator 
*/

typedef struct{
	char* value;
	int baseindex; // see bases map
} basenumber;

basenumber getNumberAndBase(int basesLength);
basenumber baseConverter(int supportedLength);
basenumber baseCalculator(basenumber number1);
int validBase(char situation[], int iterationCounter);
bool baseCheck(int base, char inputNumber[]);
char* lowerToUpper(char lowerString[]);
char* convertToDecimal(int base, char inputNumber[]);
char* convertFromDecimal(int base, char inputNumber[]);


/*
	Supported bases map (useful for the 2 arrays below and validBase function) 
	0 = BASE 2
	1 = BASE 8
	2 = BASE 10
	3 = BASE 16
*/

const int MAX_CHARS = 32;
const int SUPPORTED_BASES[] = {2,8,10,16};
const char SUPPORTED_CHARS[][17] = {"01","01234567", "0123456789", "0123456789ABCDEF"};

int main(int argc, char *argv[]) {
	printf("\n-------- / WELCOME TO C - BASEWIZARD \\ ------- \n");
	system("read -p '\nPress Enter to continue...' var");
	int tool;
	bool validTool; 
	do {
	printf("\n-------- | Select a tool(press the corresponding number) | ------- \n\n\t1.\tInteger Base Converter\n\t2.\tInteger Base Calculator\n\nTool number:\t");
	scanf("%d", &tool);
	// Clears the input buffer
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	validTool = (tool >= 1 && tool <= toolLength);
	if (!validTool){
		system("read -p '\nWrong input. Please try again...(press Enter to continue)' var");
	}
	} while(!validTool);
	int supportedLength = sizeof(SUPPORTED_BASES)/sizeof(SUPPORTED_BASES[0]);
	int cont = false;
	basenumber result;
	result.value = malloc((MAX_CHARS + 2) * sizeof(char));
	do {
		if (cont == true) {
			result = baseCalculator(result);
		}
		else{
			switch(tool){
				case 1:
					result = baseConverter(supportedLength);
				break;
				case 2:
					basenumber number1;
					number1.value = malloc((MAX_CHARS + 2) * sizeof(char));
					number1 = getNumberAndBase(supportedLength);
					result = baseCalculator(number1);
					free(number1.value);
			}
		}	
		printf("\nDo you want to use the calculator with the result? (press 0 to end or 1 to continue):\t");
		scanf("%d", &cont);
	} while (cont == true);
	free(result.value);
	return 0;
}

basenumber getNumberAndBase(int basesLength){
	basenumber inputUpper;
	// Maximum supported digits are 32 (+ \n from fgets and \0 char)
	char input[MAX_CHARS + 2];
	bool compatibleLength, baseChecker;
	do {
		// Asks as input an integer
		printf("\nType an integer (Maximum supported digits %d): \t", MAX_CHARS);
		// Replaced gets(strArr) with fgets(strArr, maxChars, stdin) for security
		fgets(input, sizeof(input), stdin);
		// Checks number of digits (2nd from the end char from fgets is \n)
		compatibleLength = (input[strlen(input) - 1] == '\n');
		if (!compatibleLength){
			// Clears input buffer for fgets
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
			printf("\nUnsupported length of digits (max %d). Try again...\n", MAX_CHARS);
		}
	} while(!compatibleLength);
	do {
		// Gets from user and checks compatibility for current and new base of the number
		inputUpper.baseindex = validBase("current", basesLength);
		// Converts possible lowercase to capital before checking (lowerToUpper)
		inputUpper.value = lowerToUpper(input);
		baseChecker = baseCheck(inputUpper.baseindex, inputUpper.value);
		if (!baseChecker){
			printf("\nThe current base does not match with the number you typed. Try again...\n");
		}
	} while(!baseChecker);
	return inputUpper;
}


// Checks if an inserted base is supported by the program
int validBase(char situation[], int iterationCounter){
	// Asks for the integer's base (checks if it's supported)
	int base, counter;
	bool isSupported = false;
	do {
		printf("\nType the %s base of the integer: \t", situation);
		scanf("%d", &base);
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

basenumber baseConverter(int supportedLength){
	printf("\n-------- | Integer Base Converter | ------- \n");
	basenumber inputNumber = getNumberAndBase(supportedLength), outputNumber;
	outputNumber.value = malloc((MAX_CHARS + 2) * sizeof(char));
	if(outputNumber.value == NULL){
		printf("\nMemory allocation to baseConverter failed...");
		exit(5);
	}
	outputNumber.baseindex = validBase("next", supportedLength); 
	if (inputNumber.baseindex == outputNumber.baseindex){
		strcpy(outputNumber.value, inputNumber.value);
	}
	else if (SUPPORTED_BASES[inputNumber.baseindex] == 10){
		strcpy(outputNumber.value, convertFromDecimal(outputNumber.baseindex, inputNumber.value));
	}
	else {
		char toDecimal[MAX_CHARS + 2];
		// Uses base 10 as middle converter
		strcpy(toDecimal, convertToDecimal(inputNumber.baseindex, inputNumber.value));
		strcpy(outputNumber.value, convertFromDecimal(outputNumber.baseindex, toDecimal));
	}
	printf("\nNumber before conversion (base %d):\t%s\nNumber after conversion (base %d):\t%s\n", SUPPORTED_BASES[inputNumber.baseindex], inputNumber.value, SUPPORTED_BASES[outputNumber.baseindex], outputNumber.value);
	free(inputNumber.value);
	return outputNumber;
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
		printf("\nMemory allocation to convertFromDecimal failed");
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
	// Reverses the elements of the remainder int array into the result char array (string)
	for (j = 0; j < digitCounter; j++){
		outputString[j] = charRemainder[digitCounter - 1 - j];
	}
	// Explicitly ends the string to avoid printing junk chars
	outputString[digitCounter] = '\0';
	free(charRemainder);
	return outputString;
}

basenumber baseCalculator(basenumber number1){
	basenumber calcResult;
	calcResult.value = malloc(MAX_CHARS * sizeof(char));
	return calcResult;
	}