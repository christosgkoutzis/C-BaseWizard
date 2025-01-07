#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "baseconverter.h"
#include "basecalculator.h"
#include "utility.h"


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
	bool isNegative = (inputNumber[0] == '-');
	int startIndex = isNegative ? 1 : 0;
	char* resultString = malloc(MAX_CHARS * sizeof(char));
	if(resultString == NULL){
		printf("Memory allocation to convertToDecimal failed\n");
		exit(3);
	}
	for (i = startIndex; i < strlen(inputNumber); i++){
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
	if (isNegative) {
		resultInteger = -resultInteger;
	}
	// Converts the integer (from resultInteger) to string and stores it to resultString 
	sprintf(resultString, "%d", resultInteger);
	return resultString;
}

char* convertFromDecimal(int base, char inputNumber[]){
	int inputInt = atoi(inputNumber), digitRemainder[MAX_CHARS], digitCounter, j;
	bool isNegative = (inputInt < 0);
	if (isNegative) {
		inputInt = -inputInt;
	}
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
	if (isNegative) {
		char* negativeOutputString = malloc((strlen(outputString) + 2) * sizeof(char));
		sprintf(negativeOutputString, "-%s", outputString);
		free(outputString);
		free(charRemainder);
		return negativeOutputString;
	}
	free(charRemainder);
	return outputString;
}