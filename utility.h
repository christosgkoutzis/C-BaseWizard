#ifndef UTILITY_H
#define UTILITY_H

typedef struct{
	char* value;
	int baseindex; // see bases map
} basenumber;

/*
	Supported bases map (useful for the 2 arrays below and validBase function) 
	0 = BASE 2
	1 = BASE 8
	2 = BASE 10
	3 = BASE 16
*/

extern const int MAX_CHARS;
extern const int SUPPORTED_BASES[4];
extern const char SUPPORTED_CHARS[][17];
extern const char MATH_OPERATORS[4];

basenumber getNumberAndBase(int basesLength);
int validBase(char situation[], int iterationCounter);
bool baseCheck(int base, char inputNumber[]);
char* lowerToUpper(char lowerString[]);
void clearInputBuffer(void);

#endif