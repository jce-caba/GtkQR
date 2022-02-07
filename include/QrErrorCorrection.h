#ifndef QRERRORCORRECTION_H_INCLUDED
#define QRERRORCORRECTION_H_INCLUDED
#include "QrDefinitions.h"
#include "QrVersion.h"

 int geterrorcorrection (QR_Data *);
 int getDataBits(QR_Data *);

 int getECCodewords (QR_Data *);
 int getNumberBlocks1 (QR_Data *);
 int getNumberDataBlocks1 (QR_Data *);
 int getNumberBlocks2 (QR_Data *);
 int getNumberDataBlocks2 (QR_Data *);


#endif // QRERRORCORRECTION_H_INCLUDED
