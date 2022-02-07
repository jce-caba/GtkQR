#ifndef QRDATATABLES_H_INCLUDED
#define QRDATATABLES_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include "QrDefinitions.h"
#include "QrVersion.h"
#include "QrErrorCorrection.h"
#include "QrDefinitions_Internal.h"




  char * padBytes(QR_Data *,int);
  const char * getModeIndicator(QR_Data *);
  const char * getEciIndicator(QR_Data *,Dictionary *,int);
  const char * getEciAssignament(QR_Data *,Dictionary *,int);

#endif // QRDATATABLES_H_INCLUDED
