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
basenumber baseCalculator(basenumber number1, int basesLength);
int validBase(char situation[], int iterationCounter);
bool baseCheck(int base, char inputNumber[]);
char* lowerToUpper(char lowerString[]);
char* convertToDecimal(int base, char inputNumber[]);
char* convertFromDecimal(int base, char inputNumber[]);
char validMathOperator(void);
void switchPositions(int *number1, int *number2);


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

const char MATH_OPERATORS[4] = {'+','-','*','/'};

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
			result = baseCalculator(result, supportedLength);
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
					result = baseCalculator(number1, supportedLength);
					free(number1.value);
			}
		}	
		printf("\nDo you want to use the calculator with the result? (press 0 to end or 1 to continue):\t");
		scanf("%d", &cont);
		// Clears the input buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	} while (cont == true);
	free(result.value);
	return 0;
}

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
		// Clears the input buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
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

basenumber baseCalculator(basenumber number1, int basesLength){
	basenumber number2 = getNumberAndBase(basesLength), calcResult;
	char* number1ToDec;
	char* number2ToDec;
	int number1Int, number2Int, base10counter;
	float resultFlo;
	calcResult.value = malloc((MAX_CHARS + 2) * sizeof(char));
	char operator = validMathOperator();
	// Converts both string numbers to base10 format
	if (SUPPORTED_BASES[number1.baseindex] != 10){
		number1ToDec = convertToDecimal(number1.baseindex, number1.value);
	}
	if (SUPPORTED_BASES[number2.baseindex] != 10){
		number2ToDec = convertToDecimal(number2.baseindex, number2.value);
	}
	// Converts to integers the base 2 numbers
	number1Int = atoi(number1ToDec);
	number2Int = atoi(number2ToDec);
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
			resultFlo = (float)(number1Int / number2Int);
			break;
	}
	// Copies as a string the float value of the number to calcResult
	sprintf(calcResult.value,"%.2f",resultFlo);
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
		// Clears the input buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		isValidInput = (convertInput == 0 || convertInput == 1);
		if (!isValidInput){
			printf("\nIncorrect input. Please try again...");
		}
	} while (!isValidInput);
	if (convertInput == true) {
		calcResult.baseindex = validBase("next", basesLength);
		strcpy(calcResult.value, convertFromDecimal(calcResult.baseindex, calcResult.value));
		printf("\nNew integer value: \t%s\nNew Base: \t%d", calcResult.value, SUPPORTED_BASES[calcResult.baseindex]);
	}
	free(number2.value);
	free(number1ToDec);
	free(number2ToDec);
	return calcResult;
}

char validMathOperator(void){
	int i;
	char mathOperator;
	bool isValidOperator = false;
	do {
	printf("\nType an operator(+,-,*,/):\t");
	scanf("%c", &mathOperator);
	// Clears the input buffer
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
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

void switchPositions(int *number1, int *number2){
	int switchSelect;
	bool isValidInput;
	do{
		printf("\nThe current position before the operation is:\n\tNumber 1:\t%d\n\tNumber 2: \t%d\nDo you want to switch positions(press 0 for no and 1 for yes)?\t", *number1, *number2);
		scanf("%d", &switchSelect);
		// Clears the input buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
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
