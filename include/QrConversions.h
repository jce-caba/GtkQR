#ifndef QRCONVERSIONS_H_INCLUDED
#define QRCONVERSIONS_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <math.h>

  char * toBinary(int);
  char * fillzeros(int,char *);
  char * fillzerosafter(int,char *);

  void most_significant_byte(char *,char *);
  void least_significant_byte(char *,char *);

  int toDecimal(char *);

  int* toDecimalarray(int,char **);

  void toBinary_n_bits(char *,int,int);

  char * number_to_char(int);



#endif // QRCONVERSIONS_H_INCLUDED
