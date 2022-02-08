#include "QrProcesses.h"
#include "QrErrorCorrection.h"
#include <stdio.h>
#include "Qrerrorcorrectioncoding.h"
#include "QrDataTables.h"
#include "QrEncode.h"
#include "QrDataAnalysis.h"
#include "QrCharacterCountIndicator.h"
#include "QrVersion.h"
#include "QrCapacity.h"
#include "QrMatrixFunction.h"
#include "QrAlignmentPatternLocations.h"
#include "QrMatrixData.h"
#include "QrMask.h"
#include "QrInformationStrings.h"
#include "QrDefinitions_Internal.h"


 char * QR_GetData(const char *,QR_Data *);
 void padding (char *,QR_Data *);
 char * errorproces(const char *value,QR_Data *data);
 char * encodeproces(Dictionaries *,QR_Data *);
 char * errorproces(const char *,QR_Data *);




char ** calculateMatrix(const char *text ,QR_Data *data )
{
   char *encode;
   char **matrix_function_QR;
   char **matrix_QR;
   char **final_matrix_QR;
   const char *format;

   encode = QR_GetData(text,data);

   if(encode == NULL )
           return NULL;


   matrix_function_QR = getMatrixFunction(data);

   getAlignment(data,matrix_function_QR);
   matrix_QR = getMatrixData(data,encode);
   free(encode);

    final_matrix_QR =getMaskMatrix(matrix_QR,matrix_function_QR,data);
    freeMatrix(matrix_QR);
    freeMatrix(matrix_function_QR);

    if(data->qrversion_number >= 7)
    {
        format = getVersionInformation(data);
        setMatrixFunctionVersion(final_matrix_QR,data,format);
    }


    format = getFormatInformation(data);
    setMatrixFunctionFormat(final_matrix_QR,data,format);

    return final_matrix_QR;
}

char * QR_GetData(const char *text ,QR_Data *data )
{
    Dictionaries dictionary;
    char *result;

    if(text == NULL)
         return NULL;


    dictionary = analyze_data(text,data);

    if (dictionary.error == 1)
    {
       data->qrversion = GTKQR_VERSION_QR_NULL;
       data->qrversion_number = GTKQR_NO_VERSION;
       data->error = "character set invalid";
       data->warning = NULL;
       data->eci_mode = NULL;
       data->num_eci_mode = 0;
       return NULL;
    }
    else if(dictionary.total_data==0)
    {
       data->qrversion_number = GTKQR_NO_VERSION;
       data->qrversion = GTKQR_VERSION_QR_NULL;
       data->error = "No data input";
       data->warning = NULL;
       free_Dictionaries(&dictionary);
       data->eci_mode = NULL;
       data->num_eci_mode = 0;
       return NULL;
    }

    if(data->isMicro==1 && data->correction_level == GTKQR_ERROR_CORRECTION_LEVEL_HIGH)
    {
        data->correction_level = GTKQR_ERROR_CORRECTION_LEVEL_QUALITY;
        data->warning = "change correction level H to Q";
    }
    else if(data->isMicro==0 && data->correction_level == GTKQR_ERROR_CORRECTION_LEVEL_NOTHING)
    {
        data->correction_level = GTKQR_ERROR_CORRECTION_LEVEL_LOW;
        data->warning = "change correction level Nothing to Low";
    }


    data->data_coding = dictionary.dictionaries[0].coding;
    data->qrversion = getMinimumVersion(dictionary.total_data,data->data_coding,data->correction_level,data->isMicro);

    if (data->qrversion == GTKQR_VERSION_QR_NULL ) {
       data->qrversion_number = GTKQR_NO_VERSION;
       data->error = "too many characters";
       data->warning = NULL;
       free_Dictionaries(&dictionary);
       data->eci_mode = NULL;
       data->num_eci_mode = 0;

       return NULL;
    }

    if(dictionary._num_dictionaries==1 && dictionary.dictionaries[0].eci_mode != GTKQR_ECI_MODE_ISO_8859_1)
    {
        data->eci_mode = (GtkQREciMode *) malloc((1)*sizeof(GtkQREciMode));
        data->eci_mode[0] = dictionary.dictionaries[0].eci_mode;
        data->num_eci_mode = 1;
    }
    else if(dictionary._num_dictionaries>1)
    {
        data->eci_mode = (GtkQREciMode *) malloc((dictionary._num_dictionaries)*sizeof(GtkQREciMode));
        data->num_eci_mode = dictionary._num_dictionaries;
        for (int i=0; i < dictionary._num_dictionaries ;i++)
            data->eci_mode[i] = dictionary.dictionaries[i].eci_mode;
    }
    else
    {
        data->eci_mode = NULL;
        data->num_eci_mode = 0;
    }


    data->qrversion_number = version_to_int(data->qrversion);
    data->num_modules = getnumbermodule(data);
    result = encodeproces(&dictionary ,data);
    free_Dictionaries(&dictionary);


    return result;

}


char * errorproces(const char *value,QR_Data *data)
{
    char ** allblocks;
    char *** group1;
    char *** group2=NULL;
    char *msg;

    allblocks = _getgroups(value,data);

    group1 = getgroup1 (allblocks,data);
    group2 = getgroup2 (allblocks,data);

    msg= getfinalmessage(value,group1,group2,data);


    freememory (allblocks);
    freememorygroup (group1);
    freememorygroup (group2);

     return msg ;
}

char * encodeproces(Dictionaries *dictionary,QR_Data *data)
{
   char *code;
   char *txt;
   int value1;
   int value2;
   const char *aux;

   value1 = getDataBits(data);
   code  = (char *) malloc( (value1 +1 )* sizeof(char));
   code[0] = '\0';

    for (unsigned int i = 0 ; i< dictionary->_num_dictionaries ; i ++)
    {

        aux = getEciIndicator(data,&dictionary->dictionaries[i],i);
        strcat(code, aux);
        aux = getEciAssignament(data,&dictionary->dictionaries[i],i);
        strcat(code, aux);


        aux = getModeIndicator(data);
        strcat(code, aux);

        value2 = getCharacterCountIndicator(data);
        txt = (char*) malloc((value2+1)* sizeof(char));
        txt[value2] = '\0';
        toBinary_n_bits(txt,dictionary->dictionaries[i].size_data,value2);
        strcat(code, txt);
        free(txt); // ok



        switch(data->data_coding)
        {

        case GTKQR_DATA_BYTE:
            txt= encondeISO_8859_1((int *)dictionary->dictionaries[i].data,dictionary->dictionaries[i].size_data);

            break;
        case GTKQR_DATA_KANJI:
            txt= encondeKanji((int *)dictionary->dictionaries[i].data,dictionary->dictionaries[i].size_data);
            break;
        case GTKQR_DATA_NUMERIC:
            txt= encondeNumeric((char *)dictionary->dictionaries[i].data);
            break;
        case GTKQR_DATA_ALPHANUMERIC:
            txt= encondeAlphaNumeric((char *)dictionary->dictionaries[i].data);
            break;
        default:

            break;
        }

        strcat(code, txt);
        free(txt);



    }


    /**  PADDING **/
    padding (code ,data);

    txt = errorproces(code,data);
    free(code);

    return txt;
}


 void padding (char * code ,QR_Data *data)
 {
    char *txt;
    int lg,lg2;
    int auxInt;
    int parity;

    lg = getDataBits (data);
    lg2 = strlen(code);

    auxInt = getTerminator(data);
    if(lg>=lg2 + auxInt)
    {
      parity =getparity(data);
      while((lg2+auxInt) % parity != 0 )
                  auxInt++;

      txt = (char *) malloc((auxInt + 1) *sizeof(char));
      txt[0] =  '\0';

      for(int i=0;i<auxInt;i++)
                       strcat(txt, "0");

      strcat(code, txt);
      free(txt);



      lg2 = lg2 +auxInt;
      if(lg > lg2)
      {
          lg = (lg-lg2) /parity ;
          txt= padBytes(data,lg);
          strcat(code, txt);
          free(txt);
      }
    }
    else
    {
         auxInt =lg-lg2;
         if(auxInt > 0)
         {
            for(int i=0;i<auxInt;i++)
                                strcat(code, "0");
         }

    }


 }


