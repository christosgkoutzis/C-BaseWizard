#ifndef BASECONVERTER_H
#define BASECONVERTER_H
#include "utility.h"

basenumber baseConverter(int supportedLength);
char* convertToDecimal(int base, char inputNumber[]);
char* convertFromDecimal(int base, char inputNumber[]);

#endif