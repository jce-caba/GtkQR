#ifndef QRENCODE_H_INCLUDED
#define QRENCODE_H_INCLUDED
#include <string.h>
#include <stdlib.h>
#include "QrConversions.h"

 char * encondeNumeric(const char *);
 char * encondeAlphaNumeric(const char *);
 char * encondeISO_8859_1(int *,int);
 int    getAlphaNumericValue(char txt);
 char * encondeKanji(int *,int);

#endif // QRENCODE_H_INCLUDED
