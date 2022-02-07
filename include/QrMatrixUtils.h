#ifndef QRMATRIXUTILS_H_INCLUDED
#define QRMATRIXUTILS_H_INCLUDED
#include <stdlib.h>
#include <QrDefinitions.h>

     void freeMatrix(char **);
     char ** createMatrix(char **,QR_Data *);
     void    copyMatrix(char **,char **,QR_Data *);

     void sumMatrix(char **,char **,QR_Data *);

#endif // QRMATRIXUTILS_H_INCLUDED
