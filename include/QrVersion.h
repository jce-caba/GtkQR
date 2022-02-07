#ifndef QRVERSION_H_INCLUDED
#define QRVERSION_H_INCLUDED
#include "QrDefinitions.h"


 int   getnumbermodule(QR_Data *);
 int   version_to_int(GtkQRVersion);
 int   getTerminator(QR_Data *);
 int   getparity(QR_Data *);

#endif // QRVERSION_H_INCLUDED
