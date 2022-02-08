#include "QrDataTables.h"

char * padBytesQR(int);
char * padBytesMicro(int);

char * padBytes(QR_Data *data,int value)
{
  int parity;

  if(data->isMicro == 1)
  {
      parity =getparity(data);

      if (parity ==4)
            return padBytesMicro(value);
      else
            return padBytesQR(value);

  }
  else
        return padBytesQR(value);


}

char * padBytesMicro(int value)
{
   char *res;

   res = (char *) malloc((4*value +1)* sizeof(char));
   res[0] = '\0';

   for (int i = 0; i < value; i =i+ 1)
             strcat(res, "0000");

   return res;
}


char * padBytesQR(int value)
 {
   char *res;
   char even[]={'1','1','1','0','1','1','0','0'};
   char  odd[]={'0','0','0','1','0','0','0','1'};

   int a= 0;
   res = (char *) malloc((8*value +1)* sizeof(char));

   for (int i = 0; i < value; i =i+ 1)
   {
      if ((i+2)% 2 == 0 )
      {
        res[a]=even[0];res[a+1]=even[1];res[a+2]=even[2];res[a+3]=even[3];
        res[a+4]=even[4]; res[a+5]=even[5]; res[a+6]=even[6]; res[a+7]=even[7];
      }
      else
      {
        res[a]=odd[0];res[a+1]=odd[1];res[a+2]=odd[2];res[a+3]=odd[3];
        res[a+4]=odd[4]; res[a+5]=odd[5]; res[a+6]=odd[6]; res[a+7]=odd[7];
      }

      a = a + 8;
   }

   res[8*value] = '\0';

   return res;
 }

 const char * getEciIndicator(QR_Data *data,Dictionary *dictionary,int num_it)
 {
   const char *txt ="";

   if (num_it == 0 && data->data_coding == GTKQR_DATA_BYTE && dictionary->eci_mode != GTKQR_ECI_MODE_ISO_8859_1)
                                 txt ="0111";
   else if (num_it > 0 && data->data_coding == GTKQR_DATA_BYTE )
                                 txt ="0111";

    return txt;
 }

 const char * getEciAssignament(QR_Data *data,Dictionary *dictionary,int num_it)
 {
   const char *txt ="";

   if(data->data_coding !=GTKQR_DATA_BYTE)
           return txt;


   switch(dictionary->eci_mode)
   {
      case GTKQR_ECI_MODE_ISO_8859_1:
             if (num_it > 0 )
                          txt ="00000011";
      break;
      case GTKQR_ECI_MODE_ISO_8859_2:
            txt ="00000100";
      break;
      case GTKQR_ECI_MODE_ISO_8859_3:
            txt ="00000101";
      break;
      case GTKQR_ECI_MODE_ISO_8859_4:
            txt ="00000110";
      break;
      case GTKQR_ECI_MODE_ISO_8859_5:
            txt ="00000111";
      break;
      case GTKQR_ECI_MODE_ISO_8859_6:
            txt ="00001000";
      break;
      case GTKQR_ECI_MODE_ISO_8859_7:
            txt ="00001001";
      break;
      case GTKQR_ECI_MODE_ISO_8859_8:
            txt ="00010000";
      break;
      case GTKQR_ECI_MODE_ISO_8859_9:
            txt ="00010001";
      break;
      case GTKQR_ECI_MODE_ISO_8859_10:
            txt ="00010010";
      break;
      case GTKQR_ECI_MODE_ISO_8859_11:
            txt ="00010011";
      break;
      case GTKQR_ECI_MODE_ISO_8859_13:
            txt ="00010101";
      break;
      case GTKQR_ECI_MODE_ISO_8859_14:
            txt ="00010110";
      break;
      case GTKQR_ECI_MODE_ISO_8859_15:
            txt ="00010111";
      break;
      case GTKQR_ECI_MODE_ISO_8859_16:
            txt ="00011000";
      break;
      case Shift_JIS:
            txt ="00100000";
      break;
      case UTF_8:
            txt ="00100110";
      break;
      default:
        break;
   }

   return txt;
 }

 const char * getModeIndicator(QR_Data *data)
{

    if(data->isMicro == 1)
    {
        if(data->qrversion == GTKQR_VERSION_M2 && data->data_coding == GTKQR_DATA_NUMERIC)
            return "0";
        else if(data->qrversion == GTKQR_VERSION_M2 && data->data_coding==GTKQR_DATA_ALPHANUMERIC)
            return "1";

        else if(data->qrversion == GTKQR_VERSION_M3 && data->data_coding == GTKQR_DATA_NUMERIC)
            return "00";
        else if(data->qrversion == GTKQR_VERSION_M3 && data->data_coding==GTKQR_DATA_ALPHANUMERIC)
            return "01";
        else if(data->qrversion == GTKQR_VERSION_M3 && data->data_coding== GTKQR_DATA_BYTE)
            return "10";
        else if(data->qrversion == GTKQR_VERSION_M3 && data->data_coding==GTKQR_DATA_KANJI)
            return "11";

        else if(data->qrversion == GTKQR_VERSION_M4 && data->data_coding == GTKQR_DATA_NUMERIC)
            return "000";
        else if(data->qrversion == GTKQR_VERSION_M4 && data->data_coding==GTKQR_DATA_ALPHANUMERIC)
            return "001";
        else if(data->qrversion == GTKQR_VERSION_M4 && data->data_coding== GTKQR_DATA_BYTE)
            return "010";
        else if(data->qrversion == GTKQR_VERSION_M4 && data->data_coding==GTKQR_DATA_KANJI)
            return "011";


        return "";
    }
    else
    {
        if(data->data_coding == GTKQR_DATA_NUMERIC)
        {
            return "0001";
        }
        else if(data->data_coding==GTKQR_DATA_ALPHANUMERIC)
        {
            return "0010";
        }
        else if(data->data_coding== GTKQR_DATA_BYTE)
        {
            return "0100";
        }
        else if(data->data_coding==GTKQR_DATA_KANJI)
        {
            return "1000";
        }
    }




   return "0001";
}
