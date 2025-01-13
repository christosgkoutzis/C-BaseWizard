#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "basesortingtool.h"
#include "baseconverter.h"
#include "utility.h"

basenumber baseSort(int basesLength){
  system("read -p '\n\n-------- | Base Sorting Tool | ------- \n\nWelcome to Base Sorting Tool. Here, you will input base numbers using the Base Converter tool (optional) and the program will sort them according to their base.\n\nPress Enter to continue...' var");
  basenumber* sortedInputs = NULL;
  int inputCounter = 0, anotherInput, baseConverterterInput;
  bool isValidInput;
  do {
    sortedInputs = realloc(sortedInputs, (inputCounter + 1) * sizeof(basenumber));
    if (sortedInputs == NULL){
      printf("\nMemory allocation to baseSort failed...");
      exit(7);
    }
    // Chooses the appropriate function to fetch the input (baseConverter or getNumberAndBase)
    do {
      printf("\nDo you want to use the Base Converter tool for this input? (press 0 for no and 1 for yes)?\t");
      scanf("%d", &baseConverterterInput);
      clearInputBuffer();
      isValidInput = (baseConverterterInput == 0 || baseConverterterInput == 1);
      if (!isValidInput){
        printf("\nIncorrect input. Please try again...");
      }
    } while (!isValidInput);
    if (baseConverterterInput){
      sortedInputs[inputCounter] = baseConverter(basesLength);
    } else {
      sortedInputs[inputCounter] = getNumberAndBase(basesLength);
    }
    inputCounter++;
    do {
      printf("\nDo you want to input another number? (press 0 for no and 1 for yes):\t");
      scanf("%d", &anotherInput);
      clearInputBuffer();
      isValidInput = (anotherInput == 0 || anotherInput == 1);
      if (!isValidInput){
        printf("\nIncorrect input. Please try again...");
      }
    } while(!isValidInput);
  } while(anotherInput);
  // stdlib.h function that applies quick sort to the array of basenumbers (4th input is the generic comparing algorithm that will be used to sort)
  qsort(sortedInputs, inputCounter, sizeof(basenumber), compareBaseNumbers);
  printf("\n-------- | Base Sorting Tool Results | ------- \n");
  for (int i = 0; i < inputCounter; i++){
    printf("\nNumber %d:\t%s (base %d)", i + 1, sortedInputs[i].value, SUPPORTED_BASES[sortedInputs[i].baseindex]);
  }
  printf("\n\nMinimum number: %s (base %d)\nMaximum number: %s (base %d)\n\nWhich base number would you like to use as the result (press its index according to the printed results)?\t", sortedInputs[0].value, SUPPORTED_BASES[sortedInputs[0].baseindex], sortedInputs[inputCounter - 1].value, SUPPORTED_BASES[sortedInputs[inputCounter - 1].baseindex]);
  int resultIndex;
  do {
    scanf("%d", &resultIndex);
    clearInputBuffer();
    isValidInput = (resultIndex >= 1 && resultIndex <= inputCounter);
    if (!isValidInput){
      printf("\nIncorrect input. Please try again...");
    }
  } while(!isValidInput);
  basenumber result = sortedInputs[resultIndex - 1];
  free(sortedInputs);
  return result;
}


int compareBaseNumbers(const void *a, const void *b){
  basenumber* number1 = (basenumber *)a;
  basenumber* number2 = (basenumber *)b;
  char* number1ToDec = convertToDecimal(number1->baseindex, number1->value);
  char* number2ToDec = convertToDecimal(number2->baseindex, number2->value);
  long long Dec1Int = strtoll(number1ToDec, NULL, 10);
  long long Dec2Int = strtoll(number2ToDec, NULL, 10);
  return Dec1Int - Dec2Int;
}