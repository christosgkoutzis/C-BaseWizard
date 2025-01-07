#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool (data type), true-false (keywords)
#include <string.h> // strlen, strcpy, strtok
#include <math.h> // pow
#include "baseconverter.h"
#include "basecalculator.h"
#include "utility.h"

#define toolLength 2
/*
	Supported tools map
	1 = Integer Base Converter
	2 = Integer Base Calculator 
*/

int main(int argc, char *argv[]) {
	printf("\n-------- / WELCOME TO C - BASEWIZARD \\ ------- \n");
	system("read -p '\nPress Enter to continue...' var");
	int tool;
	bool validTool; 
	do {
	printf("\n-------- | Select a tool(press the corresponding number) | ------- \n\n\t1.\tInteger Base Converter\n\t2.\tInteger Base Calculator\n\nTool number:\t");
	scanf("%d", &tool);
	clearInputBuffer();
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
		clearInputBuffer();
	} while (cont == true);
	free(result.value);
	printf("\n-------- | Thank you for using C-BaseWizard | ------- \n\n");
	return 0;
}

