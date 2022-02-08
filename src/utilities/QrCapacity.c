#include "QrCapacity.h"

int getCapacity(GtkQRVersion,GtkQRData,GtkQRErrorCorrectionLevel);
int getCapacity_micro_QR(GtkQRVersion,GtkQRData,GtkQRErrorCorrectionLevel);
GtkQRVersion getMinimumVersion_QR (int,GtkQRData,GtkQRErrorCorrectionLevel);
GtkQRVersion getMinimumVersion_micro_QR (int,GtkQRData,GtkQRErrorCorrectionLevel);

GtkQRVersion getMinimumVersion(int length,GtkQRData cmqr,GtkQRErrorCorrectionLevel err,short microQR)
{
    if(microQR == 1)
        return getMinimumVersion_micro_QR (length,cmqr,err);
    else
        return getMinimumVersion_QR (length,cmqr,err);
}


GtkQRVersion getMinimumVersion_micro_QR (int length,GtkQRData cmqr,GtkQRErrorCorrectionLevel err)
{
  int value=0;
  GtkQRVersion types[]={GTKQR_VERSION_M1,GTKQR_VERSION_M2,GTKQR_VERSION_M3,GTKQR_VERSION_M4};
  int a =-1;


  while(a < 3 && value<length)
  {
      a++;
      value = getCapacity_micro_QR(types[a],cmqr,err);
  }

  if(value >= length )
      return types[a];
  else
      return GTKQR_VERSION_QR_NULL;

}

GtkQRVersion getMinimumVersion_QR (int length,GtkQRData cmqr,GtkQRErrorCorrectionLevel err)
{
   int a=0;
   int value=0;
   GtkQRVersion types[]={GTKQR_VERSION_QR_1,GTKQR_VERSION_QR_2,GTKQR_VERSION_QR_3,GTKQR_VERSION_QR_4,GTKQR_VERSION_QR_5,GTKQR_VERSION_QR_6,GTKQR_VERSION_QR_7
  ,GTKQR_VERSION_QR_8,GTKQR_VERSION_QR_9,GTKQR_VERSION_QR_10,GTKQR_VERSION_QR_11,GTKQR_VERSION_QR_12,GTKQR_VERSION_QR_13,GTKQR_VERSION_QR_14,GTKQR_VERSION_QR_15,GTKQR_VERSION_QR_16,GTKQR_VERSION_QR_17,GTKQR_VERSION_QR_18,GTKQR_VERSION_QR_19,
  GTKQR_VERSION_QR_20,GTKQR_VERSION_QR_21,GTKQR_VERSION_QR_22,GTKQR_VERSION_QR_23,GTKQR_VERSION_QR_24,GTKQR_VERSION_QR_25,GTKQR_VERSION_QR_26,GTKQR_VERSION_QR_27,GTKQR_VERSION_QR_28,GTKQR_VERSION_QR_29,GTKQR_VERSION_QR_30,
  GTKQR_VERSION_QR_31,GTKQR_VERSION_QR_32,GTKQR_VERSION_QR_33,GTKQR_VERSION_QR_34,GTKQR_VERSION_QR_35,GTKQR_VERSION_QR_36,GTKQR_VERSION_QR_37,GTKQR_VERSION_QR_38,GTKQR_VERSION_QR_39,GTKQR_VERSION_QR_40,GTKQR_VERSION_QR_NULL};


   while( types[a] != GTKQR_VERSION_QR_NULL  && value<length)
   {
      value = getCapacity(types[a],cmqr,err);
      a ++;

   }

  if(value >= length )
      return types[a-1];
  else
      return GTKQR_VERSION_QR_NULL;
}

int getCapacity(GtkQRVersion version,GtkQRData cmqr,GtkQRErrorCorrectionLevel err)
{

    if(version==GTKQR_VERSION_QR_1){

        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 41;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 25;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 17;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 10;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 34;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 20;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 14;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 8;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 27;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 16;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 11;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 7;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 17;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 10;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 7;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 4;
        }
    }
    else if(version==GTKQR_VERSION_QR_2){

        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 77;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 47;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 32;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 20;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 63;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 38;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 26;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 16;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 48;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 29;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 20;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 12;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 34;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 20;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 14;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 8;
        }
    }
    else if(version==GTKQR_VERSION_QR_3){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 127;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 77;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 53;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 32;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 101;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 61;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 42;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 26;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 77;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 47;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 32;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 20;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 58;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 35;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 24;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 15;
        }
    }
    else if(version==GTKQR_VERSION_QR_4){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 187;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 114;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 78;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 48;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 149;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 90;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 62;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 38;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 111;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 67;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 46;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 28;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 82;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 50;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 34;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 21;
        }
    }
    else if(version==GTKQR_VERSION_QR_5){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 255;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 154;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 106;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 65;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 202;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 122;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 84;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 52;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 144;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 87;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 60;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 37;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 106;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 64;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 44;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 27;
        }
    }
    else if(version==GTKQR_VERSION_QR_6){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 322;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 195;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 134;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 82;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 255;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 154;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 106;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 65;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 178;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 108;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 74;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 45;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 139;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 84;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 58;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 36;
        }
    }
    else if(version==GTKQR_VERSION_QR_7){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 370;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 224;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 154;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 95;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 293;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 178;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 122;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 75;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 207;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 125;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 86;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 53;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 154;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 93;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 64;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 39;
        }
    }
    else if(version==GTKQR_VERSION_QR_8){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 461;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 279;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 192;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 118;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 365;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 221;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 152;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 93;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 259;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 157;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 108;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 66;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 202;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 122;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 84;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 52;
        }
    }
    else if(version==GTKQR_VERSION_QR_9){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 552;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 335;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 230;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 141;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 432;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 262;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 180;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 111;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 312;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 189;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 130;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 80;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 235;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 143;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 98;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 60;
        }
    }
    else if(version==GTKQR_VERSION_QR_10){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 652;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 395;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 271;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 167;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 513;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 311;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 213;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 131;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 364;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 221;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 151;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 93;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 288;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 174;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 119;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 74;
        }
    }
    else if(version==GTKQR_VERSION_QR_11){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 772;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 468;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 321;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 198;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 604;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 366;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 251;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 155;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 427;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 259;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 177;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 109;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 331;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 200;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 137;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 85;
        }
    }
    else if(version==GTKQR_VERSION_QR_12){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 883;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 535;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 367;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 226;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 691;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 419;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 287;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 177;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 489;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 296;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 203;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 125;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 374;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 227;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 155;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 96;
        }
    }
    else if(version==GTKQR_VERSION_QR_13){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1022;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 619;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 425;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 262;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 796;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 483;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 331;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 204;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 580;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 352;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 241;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 149;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 427;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 259;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 177;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 109;
        }
    }
    else if(version==GTKQR_VERSION_QR_14){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1101;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 667;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 458;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 282;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 871;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 528;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 362;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 223;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 621;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 376;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 258;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 159;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 468;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 283;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 194;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 120;
        }
    }
    else if(version==GTKQR_VERSION_QR_15){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1250;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 758;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 520;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 320;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 991;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 600;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 412;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 254;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 703;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 426;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 292;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 180;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 530;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 321;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 220;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 136;
        }
    }
    else if(version==GTKQR_VERSION_QR_16){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1408;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 854;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 586;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 361;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1082;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 656;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 450;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 277;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 775;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 470;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 322;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 198;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 602;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 365;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 250;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 154;
        }
    }
    else if(version==GTKQR_VERSION_QR_17){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1548;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 938;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 644;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 397;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1212;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 734;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 504;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 310;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 876;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 531;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 364;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 224;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 674;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 408;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 280;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 173;
        }
    }
    else if(version==GTKQR_VERSION_QR_18){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1725;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1046;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 718;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 442;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1346;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 816;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 560;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 345;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 948;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 574;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 394;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 243;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 746;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 452;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 310;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 191;
        }
    }
    else if(version==GTKQR_VERSION_QR_19){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1903;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1153;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 792;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 488;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1500;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 909;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 624;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 384;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1063;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 644;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 442;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 272;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 813;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 493;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 338;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 208;
        }
    }
    else if(version==GTKQR_VERSION_QR_20){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2061;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1249;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 858;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 528;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1600;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 970;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 666;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 410;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1159;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 702;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 482;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 297;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 919;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 557;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 382;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 235;
        }
    }
    else if(version==GTKQR_VERSION_QR_21){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2232;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1352;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 929;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 572;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1708;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1035;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 711;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 438;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1224;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 742;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 509;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 314;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 969;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 587;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 403;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 248;
        }
    }
    else if(version==GTKQR_VERSION_QR_22){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2409;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1460;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1003;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 618;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1872;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1134;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 779;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 480;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1358;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 823;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 565;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 348;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1056;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 640;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 439;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 270;
        }
    }
    else if(version==GTKQR_VERSION_QR_23){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2620;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1588;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1091;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 672;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2059;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1248;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 857;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 528;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1468;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 890;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 611;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 376;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1108;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 672;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 461;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 284;
        }
    }
    else if(version==GTKQR_VERSION_QR_24){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2812;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1704;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1171;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 721;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2188;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1326;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 911;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 561;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1588;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 963;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 661;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 407;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1228;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 744;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 511;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 315;
        }
    }
    else if(version==GTKQR_VERSION_QR_25){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3057;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1853;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1273;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 784;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2395;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1451;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 997;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 614;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1718;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1041;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 715;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 440;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1286;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 779;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 535;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 330;
        }
    }
    else if(version==GTKQR_VERSION_QR_26){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3283;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1990;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1367;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 842;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2544;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1542;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1059;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 652;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1804;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1094;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 751;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 462;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1425;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 864;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 593;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 365;
        }
    }
    else if(version==GTKQR_VERSION_QR_27){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3517;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2132;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1465;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 902;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2701;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1637;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1125;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 692;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1933;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1172;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 805;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 496;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1501;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 910;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 625;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 385;
        }
    }
    else if(version==GTKQR_VERSION_QR_28){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3669;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2223;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1528;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 940;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2857;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1732;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1190;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 732;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2085;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1263;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 868;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 534;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1581;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 958;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 658;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 405;
        }
    }
    else if(version==GTKQR_VERSION_QR_29){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3909;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2369;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1628;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1002;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3035;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1839;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1264;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 778;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2181;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1322;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 908;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 559;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1677;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1016;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 698;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 430;
        }
    }
    else if(version==GTKQR_VERSION_QR_30){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4158;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2520;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1732;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1066;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3289;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1994;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1370;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 843;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2358;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1429;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 982;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 604;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1782;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1080;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 742;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 457;
        }
    }
    else if(version==GTKQR_VERSION_QR_31){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4417;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2677;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1840;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1132;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3486;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2113;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1452;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 894;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2473;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1499;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1030;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 634;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 1897;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1150;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 790;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 486;
        }
    }
    else if(version==GTKQR_VERSION_QR_32){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4686;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2840;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1952;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1201;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3693;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2238;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1538;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 947;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2670;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1618;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1112;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 684;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2022;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1226;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 842;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 518;
        }
    }
    else if(version==GTKQR_VERSION_QR_33){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4965;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3009;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2068;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1273;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3909;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2369;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1628;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1002;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2805;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1700;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1168;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 719;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2157;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1307;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 898;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 553;
        }
    }
    else if(version==GTKQR_VERSION_QR_34){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5253;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3183;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2188;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1347;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4134;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2506;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1722;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1060;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2949;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1787;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1228;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 756;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2301;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1394;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 958;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 590;
        }
    }
    else if(version==GTKQR_VERSION_QR_35){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5529;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3351;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2303;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1417;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4343;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2632;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1809;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1113;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3081;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1867;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1283;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 790;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2361;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1431;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 983;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 605;
        }
    }
    else if(version==GTKQR_VERSION_QR_36){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5836;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3537;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2431;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1496;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4588;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2780;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1911;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1176;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3244;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1966;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1351;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 832;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2524;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1530;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1051;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 647;
        }
    }
    else if(version==GTKQR_VERSION_QR_37){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 6153;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3729;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2563;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1577;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 4775;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2894;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1989;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1224;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3417;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2071;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1423;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 876;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2625;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1591;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1093;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 673;
        }
    }
    else if(version==GTKQR_VERSION_QR_38){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 6479;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3927;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2699;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1661;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5039;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3054;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2099;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1292;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3599;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2181;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1499;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 923;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2735;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1658;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1139;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 701;
        }
    }
    else if(version==GTKQR_VERSION_QR_39){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 6743;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 4087;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2809;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1729;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5313;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3220;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2213;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1362;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3791;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2298;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1579;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 972;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 2927;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1774;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1219;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 750;
        }
    }
    else if(version==GTKQR_VERSION_QR_40){
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 7089;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 4296;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2953;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1817;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 5596;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 3391;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 2331;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1435;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3993;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 2420;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1663;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 1024;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_HIGH){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 3057;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 1852;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 1273;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 784;
        }
    }


  return -1;
}

int getCapacity_micro_QR(GtkQRVersion type,GtkQRData cmqr,GtkQRErrorCorrectionLevel err)
{



  if(type == GTKQR_VERSION_M1 && cmqr==GTKQR_DATA_NUMERIC && err==GTKQR_ERROR_CORRECTION_LEVEL_NOTHING )
               return 5;
  else if (type == GTKQR_VERSION_M2)
  {
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){

          if(cmqr==GTKQR_DATA_NUMERIC)
                return 10;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 6;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){

          if(cmqr==GTKQR_DATA_NUMERIC)
                return 8;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 5;

        }

  }
  else if (type == GTKQR_VERSION_M3)
  {
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 23;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 14;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 9;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 6;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 18;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 11;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 7;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 4;
        }
  }
  else if (type == GTKQR_VERSION_M4)
  {
        if(err==GTKQR_ERROR_CORRECTION_LEVEL_LOW){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 35;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 21;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 15;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 9;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 30;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 18;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 13;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 8;
        }
        else if(err==GTKQR_ERROR_CORRECTION_LEVEL_QUALITY){
          if(cmqr==GTKQR_DATA_NUMERIC)
                return 21;
          else if(cmqr== GTKQR_DATA_ALPHANUMERIC)
                return 13;
          else if(cmqr==GTKQR_DATA_BYTE)
                return 9;
          else if(cmqr==GTKQR_DATA_KANJI)
                return 5;
        }

  }



  return -1;
}
