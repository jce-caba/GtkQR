#ifndef QRERRORCORRECTIONCODING_H_INCLUDED
#define QRERRORCORRECTIONCODING_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "QrDefinitions.h"
#include "QrErrorCorrection.h"
#include "QrGeneratorPolynomial.h"
#include "QrConversions.h"
#include "Qrlog.h"
#include "Qrremainderbits.h"
#include "QrVersion.h"

   char ** _getgroups(const char *,QR_Data *);
   void  freememory (char **);
   void  freememorygroup (char ***);
   char *** getgroup1(char **,QR_Data *);
   char *** getgroup2(char **,QR_Data *);
   char *  getfinalmessage(const char *,char ***,char ***,QR_Data *data);














#endif // QRERRORCORRECTIONCODING_H_INCLUDED
