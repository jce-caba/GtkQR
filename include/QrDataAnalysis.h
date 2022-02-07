#ifndef QRDATAANALYSIS_H_INCLUDED
#define QRDATAANALYSIS_H_INCLUDED
#include "Kanji_character_set.h"
#include <string.h>
#include <stdlib.h>
#include <QrDefinitions_Internal.h>

 Dictionaries analyze_data(const char *,QR_Data *);
 void free_Dictionaries(Dictionaries *);
 TypeImage getTypeImage(const char *);



#endif // QRDATAANALYSIS_H_INCLUDED
