#ifndef QRMATRIXDATA_H_INCLUDED
#define QRMATRIXDATA_H_INCLUDED
#include <QrDefinitions.h>
#include <string.h>
#include "QrAlignmentPatternLocations.h"

    char ** getMatrixData(QR_Data *,const char *);


    void freeMatrix(char **);

#endif // QRMATRIXDATA_H_INCLUDED


