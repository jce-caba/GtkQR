#include "QrVersion.h"


 int getnumbermodule(QR_Data *data)
 {
     int version;

    if (data->isMicro==1)
    {
        switch(data->qrversion)
        {
        case GTKQR_VERSION_M1:
            version = 11;
            break;
        case GTKQR_VERSION_M2:
            version = 13;
            break;
        case GTKQR_VERSION_M3:
            version = 15;
            break;
        default:
            version = 17;
            break;
        }
    }
    else
    {
      version = 21 + (data->qrversion_number -1) *4;

      if (version > 177)
             version = 177;
      else if (version < 21)
             version = 21;
    }

     return version;
 }

 int version_to_int(GtkQRVersion version)
 {
     if(version==GTKQR_VERSION_QR_1)
             return 1;
     else if(version==GTKQR_VERSION_QR_2)
             return 2;
     else if(version==GTKQR_VERSION_QR_3)
             return 3;
     else if(version==GTKQR_VERSION_QR_4)
             return 4;
     else if(version==GTKQR_VERSION_QR_5)
             return 5;
     else if(version==GTKQR_VERSION_QR_6)
             return 6;
     else if(version==GTKQR_VERSION_QR_7)
             return 7;
     else if(version==GTKQR_VERSION_QR_8)
             return 8;
     else if(version==GTKQR_VERSION_QR_9)
             return 9;
     else if(version==GTKQR_VERSION_QR_10)
             return 10;
     else if(version==GTKQR_VERSION_QR_11)
             return 11;
     else if(version==GTKQR_VERSION_QR_12)
             return 12;
     else if(version==GTKQR_VERSION_QR_13)
             return 13;
     else if(version==GTKQR_VERSION_QR_14)
             return 14;
     else if(version==GTKQR_VERSION_QR_15)
             return 15;
     else if(version==GTKQR_VERSION_QR_16)
             return 16;
     else if(version==GTKQR_VERSION_QR_17)
             return 17;
     else if(version==GTKQR_VERSION_QR_18)
             return 18;
     else if(version==GTKQR_VERSION_QR_19)
             return 19;
     else if(version==GTKQR_VERSION_QR_20)
             return 20;
     else if(version==GTKQR_VERSION_QR_21)
             return 21;
     else if(version==GTKQR_VERSION_QR_22)
             return 22;
     else if(version==GTKQR_VERSION_QR_23)
             return 23;
     else if(version==GTKQR_VERSION_QR_24)
             return 24;
     else if(version==GTKQR_VERSION_QR_25)
             return 25;
     else if(version==GTKQR_VERSION_QR_26)
             return 26;
     else if(version==GTKQR_VERSION_QR_27)
             return 27;
     else if(version==GTKQR_VERSION_QR_28)
             return 28;
     else if(version==GTKQR_VERSION_QR_29)
             return 29;
     else if(version==GTKQR_VERSION_QR_30)
             return 30;
     else if(version==GTKQR_VERSION_QR_31)
             return 31;
     else if(version==GTKQR_VERSION_QR_32)
             return 32;
     else if(version==GTKQR_VERSION_QR_33)
             return 33;
     else if(version==GTKQR_VERSION_QR_34)
             return 34;
     else if(version==GTKQR_VERSION_QR_35)
             return 35;
     else if(version==GTKQR_VERSION_QR_36)
             return 36;
     else if(version==GTKQR_VERSION_QR_37)
             return 37;
     else if(version==GTKQR_VERSION_QR_38)
             return 38;
     else if(version==GTKQR_VERSION_QR_39)
             return 39;
     else if(version==GTKQR_VERSION_QR_40)
             return 40;
     else if(version==GTKQR_VERSION_QR_NULL)
             return 41;
     else if(version==GTKQR_VERSION_M1)
             return GTKQR_VERSION_NUMBER_M1;
     else if(version==GTKQR_VERSION_M2)
             return GTKQR_VERSION_NUMBER_M2;
     else if(version==GTKQR_VERSION_M3)
             return GTKQR_VERSION_NUMBER_M3;
     else if(version==GTKQR_VERSION_M4)
             return GTKQR_VERSION_NUMBER_M4;


     return GTKQR_NO_VERSION;
 }

 int getTerminator(QR_Data *data)
 {
     if(data->qrversion==GTKQR_VERSION_M1)
             return 3;
     else if(data->qrversion==GTKQR_VERSION_M2)
             return 5;
     else if(data->qrversion==GTKQR_VERSION_M3)
             return 7;
     else if(data->qrversion==GTKQR_VERSION_M4)
             return 9;
     else
             return 4;

 }

 int getparity (QR_Data *data)
 {
     if(data->qrversion==GTKQR_VERSION_M1 || data->qrversion==GTKQR_VERSION_M3 )
        return 4;
     else
        return 8;

 }
