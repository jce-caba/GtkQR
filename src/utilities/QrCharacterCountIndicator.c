#include "QrCharacterCountIndicator.h"

 int getCharacterCountIndicator(QR_Data *data)
 {

    if(data->isMicro==1)
    {
        if(data->qrversion == GTKQR_VERSION_M1)
        {
            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 3;

        }
        else if(data->qrversion == GTKQR_VERSION_M2)
        {
            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 4;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 3;
        }
        else if(data->qrversion == GTKQR_VERSION_M3)
        {
            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 5;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 4;
            else  if (data->data_coding == GTKQR_DATA_BYTE)
                return 4;
            else  if (data->data_coding == GTKQR_DATA_KANJI)
                return 3;
        }
        else if(data->qrversion == GTKQR_VERSION_M4)
        {
            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 6;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 5;
            else  if (data->data_coding == GTKQR_DATA_BYTE)
                return 5;
            else  if (data->data_coding == GTKQR_DATA_KANJI)
                return 4;
        }


    }
    else
    {
        if(data->qrversion_number >=1 && data->qrversion_number <=9)
        {
            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 10;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 9;
            else  if (data->data_coding == GTKQR_DATA_BYTE)
                return 8;
            else  if (data->data_coding == GTKQR_DATA_KANJI)
                return 8;

        }
        else if(data->qrversion_number >=10 && data->qrversion_number <= 26)
        {

            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 12;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 11;
            else  if (data->data_coding == GTKQR_DATA_BYTE)
                return 16;
            else  if (data->data_coding == GTKQR_DATA_KANJI)
                return 10;

        }
        else if(data->qrversion_number >=27 && data->qrversion_number <= 40)
        {

            if (data->data_coding == GTKQR_DATA_NUMERIC)
                return 14;
            else  if (data->data_coding == GTKQR_DATA_ALPHANUMERIC)
                return 13;
            else  if (data->data_coding == GTKQR_DATA_BYTE)
                return 16;
            else  if (data->data_coding == GTKQR_DATA_KANJI)
                return 12;

        }
    }



   return 0;
 }

