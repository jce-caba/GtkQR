#ifndef QrDefinitions_INTERNAL_H_INCLUDED
#define QrDefinitions_INTERNAL_H_INCLUDED
#include "QrDefinitions.h"

    typedef enum  {

      TipeJPG,TipePNG,TypeBMP ,TypeIco ,TypeImageInvalid

    } TypeImage;



    typedef enum  {

      TipeChar,TipeInt,Type_invalid

    } TypeData;





    typedef struct  {

      GtkQREciMode eci_mode;
      GtkQRData coding;
      void *data;
      TypeData typedata;
      unsigned int size_data;
      short free_memory;

    } Dictionary;

    typedef struct  {

      Dictionary *dictionaries;
      unsigned int _num_dictionaries;

      short error;
      unsigned int total_data;


    } Dictionaries;




#endif // QrDefinitions_INTERNAL_H_INCLUDED
