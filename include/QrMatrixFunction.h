#ifndef QRMATRIXFUNCTION_H_INCLUDED
#define QRMATRIXFUNCTION_H_INCLUDED
#include <string.h>
#include <QrDefinitions.h>
#include <stdlib.h>

 char ** getMatrixFunction(QR_Data *);
 void setMatrixFunctionFormat(char **,QR_Data *,const char *);
 void setMatrixFunctionVersion(char **,QR_Data *,const char *);


#endif // QRMASK_H_INCLUDED

