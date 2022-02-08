#include "QrDataAnalysis.h"
#include "QrCapacity.h"
#include "8859_1_character_set.h"
#include "Kanji_character_set.h"
#include "8859_2_character_set.h"
#include "8859_3_character_set.h"
#include "8859_4_character_set.h"
#include "8859_5_character_set.h"
#include "8859_6_character_set.h"
#include "8859_7_character_set.h"
#include "8859_8_character_set.h"
#include "8859_9_character_set.h"
#include "8859_10_character_set.h"
#include "8859_11_character_set.h"
#include "8859_13_character_set.h"
#include "8859_14_character_set.h"
#include "8859_15_character_set.h"
#include "8859_16_character_set.h"
#include "JIS8_character_set.h"

 typedef   int (*FUNCTION_POT)(int);

 int isNumeric(const char *);
 int isAlphaNumeric(const char *);

 int is_8859_1(int,int **);
 int is_type(int,int **,int **,FUNCTION_POT);

 int get_UTF8(const char *,int **);
 int get_unicode(const char *,int *,int **,int);

 void  complex_data(const char *,Dictionaries *,int *,int);
 int   check_chunk (int,int,int **,FUNCTION_POT);

 int * make_copy (int,int,int **,FUNCTION_POT);

int isNumeric(const char *txt)
{
    int lg;
    int a =0;
    int result =1;

    if(txt==NULL)
          return 1;

    lg= strlen(txt);

    while(a<lg &&result>0)
    {
      if( (int) txt[a] < 48 || (int) txt[a] > 57 )
             result=0;
      else
             a++;
    }


    return result;
}

int isAlphaNumeric(const char *txt)
{
    int lg;
    int a =0;
    int result =1;

    if(txt==NULL)
          return 1;

    lg= strlen(txt);

    while(a<lg &&result>0)
    {
      if( (int) txt[a] >= 48 && (int) txt[a] <= 57 )
             a++;
      else if( (int) txt[a] >= 65 && (int) txt[a] <= 90 )
             a++;
      else if( (int) txt[a] == 32 || (int) txt[a] == 36 || (int) txt[a] == 37 || (int) txt[a] == 42 ||
               (int) txt[a] == 43 || (int) txt[a] == 45 || (int) txt[a] == 46 || (int) txt[a] == 47  || (int) txt[a] == 58 )
             a++;
      else
             result=0;
    }

    return result;
}



int is_8859_1(int total_lenght,int **values)
{
    int result =1;
    int a =0;
    int value1;

    while (a< total_lenght && result ==1 )
    {
         value1 = values[0][a];



         if( value1 > 0 && value1 <= 127)
                           a++;
         else if( value1 > 161 && value1 <= 255)
                           a++;
         else
            result = 0;

    }


    return result;
}

int is_type(int total_lenght,int **valuesIN,int **valuesOUT,FUNCTION_POT _f)
{
    int a =0;
    int value1;
    int result =1;

    while (a< total_lenght && result ==1 )
    {
        value1 = _f(valuesIN[0][a]);
        if(value1>0)
        {
            valuesOUT[0][a]=value1;
            a++;
        }
        else
           result =0;

    }


   return result;
}

int check_chunk (int start,int stop,int **valuesIN,FUNCTION_POT _f)
{
    int a =start;
    int value1;
    int result =1;

    while (a< stop && result ==1 )
    {
        value1 = _f(valuesIN[0][a]);
        if(value1>0)
        {
            a++;
        }
        else
           result =0;

    }


   return a;
}

int * make_copy (int start,int stop,int **valuesIN,FUNCTION_POT _f)
{
   int *values_out=NULL;
   int a = 0;

   values_out = (int *) malloc((stop - start)*sizeof(int));
   for(int i = start; i < stop ; i++)
   {
       values_out[a]=_f(valuesIN[0][i]);
       a++;
   }


   return values_out;
}


int get_unicode(const char * value,int *total_lenght,int **values,int max_lenght)
{
    int result = 1;
    int lg = strlen ( value );
    int aux1 ,aux2,aux3,aux4;
    int a=0;

    *total_lenght=0;

    *values = (int *) malloc((lg)*sizeof(int));

    while (a< lg && result ==1 )
    {
        aux1 = (int) value[a];

        if( aux1 > 0 && aux1 <= 127) {
           // 1 bute

           values[0][*total_lenght]=aux1;
           a++;
           *total_lenght=*total_lenght + 1;
        }
        else
        {
           if (  max_lenght < 2 || a +1 >= lg )
           {
             result=0;
             goto finish;
           }

           aux1 = (int)value[a] & -32 ;
           aux2 = (int)value[a+1] & -64;

           if(aux1 == -64 && aux2 == -128 ) {

                aux1 = (int)value[a+1] & 63 ;
                aux2 = (int)value[a] & 31 ;
                values[0][*total_lenght]=  64*aux2  + aux1 ;
                *total_lenght=*total_lenght + 1;
                a=a+2;

           }
           else
           {
               // 3 bytes
               if ( max_lenght < 3 || a +2 >= lg )
               {
                 result=0;
                 goto finish;
               }


               aux1 = (int) value[a] & -16;
               aux2 = (int)value[a+1] & -128;
               aux3 = (int)value[a+2] & -128;

               if(aux1 == -32&& aux2 == -128 && aux3 == -128){

                  aux1 = (int) value[a+2] & 63;
                  aux2 = (int) value[a+1] & 63;
                  aux3 = (int) value[a] & 15;

                  values[0][*total_lenght] = 4096*aux3 +64*aux2 + aux1 ;
                  *total_lenght=*total_lenght + 1;
                  a=a+3;
               }
               else
               {
                   // 4 bytes
                   if ( max_lenght < 4 || a +3 >= lg )
                   {
                      result=0;
                      goto finish;
                   }

                   aux1 = (int) value[a] & -8; // -16 -112 -114 -96
                   aux2 = (int)value[a+1] & -64 ;
                   aux3 = (int)value[a+2] & -64;
                   aux4 = (int)value[a+3] & -64;

                   if(aux1 == -16 && aux2 == -128 && aux3 == -128 && aux4 == -128){

                      aux1 = (int) value[a+3] & 63;
                      aux2 = (int) value[a+2] & 63;
                      aux3 = (int) value[a+1] & 63;
                      aux4 = (int) value[a] & 7;
                      values[0][*total_lenght] = 262144*aux4 + 4096*aux3+64*aux2 + aux1 ;
                      *total_lenght=*total_lenght + 1;
                      a=a+4;
                   }
                   else
                     result=0;

               }

           }
        }
    }

finish:

    if(result ==0)
    {
        free(*values);
        *total_lenght=-1;
        *values=NULL;
    }
    else
    {
       for (int z=*total_lenght ;z<lg ;z++)
            values[0][z] = -1;
    }

    return result;
}

 int get_UTF8(const char * value,int **values)
 {
    int result = 1;
    int lg = strlen ( value );
    int aux1 ;
    int a=0;

     *values = (int *) malloc((lg)*sizeof(int));


    while (a< lg && result ==1 )
    {
        aux1 = (int) value[a];

        if( aux1 > 0 && aux1 <= 127)
        {
            // 1 bute
            values[0][a]=aux1;
        }
        else
        {
             aux1 = (int)value[a] & -32 ; // format 110yyyyy
             if(aux1 == -64 )
             {
                values[0][a]=((int)value[a] & 31) + 192 ;
             }
             else
             {
                 aux1 = (int)value[a] & -64 ; // format 10xxxxxx
                 if(aux1 == -128 )
                 {
                    values[0][a]=((int)value[a] & 63) + 128 ;
                 }
                 else
                 {
                     aux1 = (int)value[a] & -16 ; // format 1110zzzz
                     if(aux1 == -32 )
                     {
                        values[0][a]=((int)value[a] & 15) + 224 ;
                     }
                     else
                     {
                        aux1 = (int)value[a] & -8 ; // format 11110uuu
                        if(aux1 == -16 )
                        {
                           values[0][a]=((int)value[a] & 7) + 240 ;
                        }
                        else
                           result = 0;
                     }
                 }
             }
        }

        a++;
    }
    if(result ==0)
    {
        free(*values);
        values=NULL;
    }

    return result;
 }

 Dictionaries analyze_data(const char *text,QR_Data *data)
 {
    int result ;
    int counter = 0;
    Dictionaries dictionaries;
    Dictionary   *dictionary;
    int *values=NULL;
    int *values_out=NULL;
    int length_unicode;
    int length_utf8;

    FUNCTION_POT _functions[15];
    GtkQREciMode   ecis[15] ;


    dictionaries.error=1;
    dictionaries.dictionaries =NULL;
    dictionaries._num_dictionaries=0;

    if (isNumeric(text) )
    {
        length_unicode = strlen(text);
        dictionaries.error=0;
        dictionaries.total_data = length_unicode;
        dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
        dictionary->coding =GTKQR_DATA_NUMERIC;
        dictionary->eci_mode =GTKQR_ECI_MODE_ISO_8859_1;
        dictionary->data =(void *)text;
        dictionary->typedata =TipeChar;
        dictionary->size_data =length_unicode;
        dictionary->free_memory =0;
        dictionaries.dictionaries = dictionary;
        dictionaries._num_dictionaries=1;
    }
    else if (isAlphaNumeric(text) )
    {
        length_unicode = strlen(text);
        dictionaries.error=0;
        dictionaries.total_data = length_unicode;
        dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
        dictionary->coding =GTKQR_DATA_ALPHANUMERIC;
        dictionary->eci_mode =GTKQR_ECI_MODE_ISO_8859_1;
        dictionary->data =(void *)text;
        dictionary->typedata =TipeChar;
        dictionary->size_data =length_unicode;
        dictionary->free_memory =0;
        dictionaries.dictionaries = dictionary;
        dictionaries._num_dictionaries=1;
    }
    else
    {
        result = get_unicode(text,&length_unicode,&values,4); //aqui
        if(result == 0)
            goto finish;

        // ** CHECK ISO 8850_1
        if (is_8859_1(length_unicode,&values))
        {
            dictionaries.error=0;
            dictionaries.total_data = length_unicode;
            dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
            dictionary->coding =GTKQR_DATA_BYTE;
            dictionary->eci_mode =GTKQR_ECI_MODE_ISO_8859_1;
            dictionary->data =(void *)values;
            dictionary->typedata =TipeInt;
            dictionary->size_data =length_unicode;
            dictionary->free_memory =1;
            dictionaries.dictionaries = dictionary;
            dictionaries._num_dictionaries=1;
        }
        else if( !data->isMicro && data->enable_UTF8)
        {
            // ** CHECK UTF 8
            free(values);
            result =get_UTF8(text,&values);
            if(result == 0)
                goto finish;

            length_utf8 = strlen(text);
            dictionaries.error=0;
            dictionaries.total_data = length_utf8 +12;
            dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
            dictionary->coding =GTKQR_DATA_BYTE;
            dictionary->eci_mode =UTF_8;
            dictionary->data =(void *)values;
            dictionary->typedata =TipeInt;
            dictionary->size_data =length_utf8;
            dictionary->free_memory =1;
            dictionaries.dictionaries = dictionary;
            dictionaries._num_dictionaries=1;

        }
        else if( !data->isMicro)
        {
           //check isos code
           values_out = (int *) malloc((length_unicode)*sizeof(int));
           ecis[0] = GTKQR_ECI_MODE_ISO_8859_2 ; ecis[1] = GTKQR_ECI_MODE_ISO_8859_3 ; ecis[2] = GTKQR_ECI_MODE_ISO_8859_4 ;
           ecis[3] = GTKQR_ECI_MODE_ISO_8859_5 ; ecis[4] = GTKQR_ECI_MODE_ISO_8859_6 ; ecis[5] = GTKQR_ECI_MODE_ISO_8859_7 ;
           ecis[6] = GTKQR_ECI_MODE_ISO_8859_8 ; ecis[7] = GTKQR_ECI_MODE_ISO_8859_9 ; ecis[8] = GTKQR_ECI_MODE_ISO_8859_10 ;
           ecis[9] = GTKQR_ECI_MODE_ISO_8859_11 ; ecis[10] = GTKQR_ECI_MODE_ISO_8859_13 ; ecis[11] = GTKQR_ECI_MODE_ISO_8859_14 ;
           ecis[12] = GTKQR_ECI_MODE_ISO_8859_15 ; ecis[13] = GTKQR_ECI_MODE_ISO_8859_16 ; ecis[14] = Shift_JIS ;

           _functions[0] = &get8859_2_character; _functions[1] = &get8859_3_character; _functions[2] = &get8859_4_character;
           _functions[3] = &get8859_5_character; _functions[4] = &get8859_6_character; _functions[5] = &get8859_7_character;
           _functions[6] = &get8859_8_character; _functions[7] = &get8859_9_character; _functions[8] = &get8859_10_character;
           _functions[9] = &get8859_11_character; _functions[10] = &get8859_13_character; _functions[11] = &get8859_14_character;
           _functions[12] = &get8859_15_character; _functions[13] = &get8859_16_character; _functions[14] = &getJIS8_character;

            result=0; counter = 0;

            while (counter < 15 && !result)
            {
                if(is_type(length_unicode,&values,&values_out,_functions[counter]))
                    result = 1;
                else
                    counter ++;
            }

            if(result)
            {
                dictionaries.error=0;
                dictionaries.total_data = length_unicode +12;
                dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
                dictionary->coding =GTKQR_DATA_BYTE;
                dictionary->eci_mode =ecis[counter];
                dictionary->data =(void *)values_out;
                dictionary->typedata =TipeInt;
                dictionary->size_data =length_unicode;
                dictionary->free_memory =1;
                dictionaries.dictionaries = dictionary;
                dictionaries._num_dictionaries=1;
                free(values);
            }
            else if(is_type(length_unicode,&values,&values_out,&getKanji_character)) //check kanji
            {
                dictionaries.error=0;
                dictionaries.total_data = length_unicode;
                dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
                dictionary->coding =GTKQR_DATA_KANJI;
                dictionary->eci_mode =GTKQR_ECI_MODE_ISO_8859_1;
                dictionary->data =(void *)values_out;
                dictionary->typedata =TipeInt;
                dictionary->size_data =length_unicode;
                dictionary->free_memory =1;
                dictionaries.dictionaries = dictionary;
                dictionaries._num_dictionaries=1;
                free(values);
            }
            else
                free(values_out);
        }
        else
        {
           //check kanji
            values_out = (int *) malloc((length_unicode)*sizeof(int));
            if(is_type(length_unicode,&values,&values_out,&getKanji_character))
            {
                dictionaries.error=0;
                dictionaries.total_data = length_unicode;
                dictionary = (Dictionary *) malloc((1)*sizeof(Dictionary));
                dictionary->coding =GTKQR_DATA_KANJI;
                dictionary->eci_mode =GTKQR_ECI_MODE_ISO_8859_1;
                dictionary->data =(void *)values_out;
                dictionary->typedata =TipeInt;
                dictionary->size_data =length_unicode;
                dictionary->free_memory =1;
                dictionaries.dictionaries = dictionary;
                dictionaries._num_dictionaries=1;
                free(values);
            }
            else
                free(values_out);
        }


    }


    if(values!=NULL && dictionaries.error==1 && !data->isMicro)
                        complex_data(text,&dictionaries,values,length_unicode);


    if(values!=NULL && dictionaries.error==1)
                          free(values);



finish:

    return dictionaries;
 }

 void free_Dictionaries(Dictionaries *dictionary)
 {
     if(dictionary->dictionaries ==NULL)
        return;


   for(int i=0;i< dictionary->_num_dictionaries; i++ )
   {
       if(dictionary->dictionaries[i].free_memory==1)
       {
           if(dictionary->dictionaries[i].typedata==TipeChar)
              free ((char *)dictionary->dictionaries[i].data);
           else  if(dictionary->dictionaries[i].typedata==TipeInt)
              free ((int *)dictionary->dictionaries[i].data);
       }
   }

   free (dictionary->dictionaries);

 }

 void  complex_data(const char *text,Dictionaries *dictionaries,int *values,int total)
 {
    int watch_dog=0;
    int extra_data=0;
    int result = 1;
    int counter = 0;
    int start =0;
    int chunk ;
    int *values_out=NULL;

    FUNCTION_POT _functions[16];
    GtkQREciMode   ecis[16] ;

    ecis[0] = GTKQR_ECI_MODE_ISO_8859_1 ;
    ecis[1] = GTKQR_ECI_MODE_ISO_8859_2 ; ecis[2] = GTKQR_ECI_MODE_ISO_8859_3 ; ecis[3] = GTKQR_ECI_MODE_ISO_8859_4 ;
    ecis[4] = GTKQR_ECI_MODE_ISO_8859_5 ; ecis[5] = GTKQR_ECI_MODE_ISO_8859_6 ; ecis[6] = GTKQR_ECI_MODE_ISO_8859_7 ;
    ecis[7] = GTKQR_ECI_MODE_ISO_8859_8 ; ecis[8] = GTKQR_ECI_MODE_ISO_8859_9 ; ecis[9] = GTKQR_ECI_MODE_ISO_8859_10 ;
    ecis[10] = GTKQR_ECI_MODE_ISO_8859_11 ; ecis[11] = GTKQR_ECI_MODE_ISO_8859_13 ; ecis[12] = GTKQR_ECI_MODE_ISO_8859_14 ;
    ecis[13] = GTKQR_ECI_MODE_ISO_8859_15 ; ecis[14] = GTKQR_ECI_MODE_ISO_8859_16 ; ecis[15] = Shift_JIS ;

    _functions[0] = &get8859_1_character;
    _functions[1] = &get8859_2_character; _functions[2] = &get8859_3_character; _functions[3] = &get8859_4_character;
    _functions[4] = &get8859_5_character; _functions[5] = &get8859_6_character; _functions[6] = &get8859_7_character;
    _functions[7] = &get8859_8_character; _functions[8] = &get8859_9_character; _functions[9] = &get8859_10_character;
    _functions[10] = &get8859_11_character; _functions[11] = &get8859_13_character; _functions[12] = &get8859_14_character;
    _functions[13] = &get8859_15_character; _functions[14] = &get8859_16_character; _functions[15] = &getJIS8_character;


     while (result && start < total)
     {
        chunk = check_chunk (start,total,&values,_functions[counter]);

        if(chunk == start)
        {
            counter++;
            watch_dog++;

            if(watch_dog >=16)
                result= 0;
        }
        else
        {
            watch_dog=0;

            if (dictionaries->_num_dictionaries == 0)
                 dictionaries->dictionaries = (Dictionary *) malloc((1)*sizeof(Dictionary));
            else
                 dictionaries->dictionaries = (Dictionary *) realloc(dictionaries->dictionaries, (dictionaries->_num_dictionaries + 1)*sizeof(Dictionary));

            dictionaries->dictionaries[dictionaries->_num_dictionaries].coding =GTKQR_DATA_BYTE;
            dictionaries->dictionaries[dictionaries->_num_dictionaries].eci_mode =ecis[counter];
            values_out =  make_copy (start,chunk,&values,_functions[counter]);
            dictionaries->dictionaries[dictionaries->_num_dictionaries].data =(void *)values_out;
            dictionaries->dictionaries[dictionaries->_num_dictionaries].typedata =TipeInt;
            dictionaries->dictionaries[dictionaries->_num_dictionaries].size_data =chunk - start;
            dictionaries->dictionaries[dictionaries->_num_dictionaries].free_memory =1;
            extra_data = extra_data + chunk - start + 16;

            dictionaries->_num_dictionaries=dictionaries->_num_dictionaries + 1;

            start=chunk ;
            counter++;
        }

        if(counter >=16)
            counter =0;

     }



     if(result)
     {
         dictionaries->error=0;

         if(dictionaries->dictionaries[0].eci_mode == GTKQR_ECI_MODE_ISO_8859_1)
                   dictionaries->total_data = extra_data -16;
         else
                   dictionaries->total_data = extra_data;

     }
     else
     {
         // jas errors
         free_Dictionaries(dictionaries);
     }

 }

 TypeImage getTypeImage(const char * text)
 {
    int lg;

    if(text == NULL || strlen(text) < 5)
        return TypeImageInvalid;

    lg=strlen(text);

    if ((text[lg-3]== 'P' || text[lg-3]== 'p' ) &&  (text[lg-2]== 'n' || text[lg-2]=='N' ) &&  (text[lg-1]== 'g' || text[lg-1]== 'G' ))
                                return TipePNG;
    else  if ((text[lg-3]== 'B' || text[lg-3]== 'b' ) &&  (text[lg-2]== 'm' || text[lg-2]=='M' ) &&  (text[lg-1]== 'p' || text[lg-1]== 'P' ))
                                return TypeBMP;
    else if ((text[lg-3]== 'I' || text[lg-3]== 'i' ) &&  (text[lg-2]== 'C' || text[lg-2]=='c' ) &&  (text[lg-1]== 'o' || text[lg-1]== 'O' ))
                                return TypeIco;
    else if ((text[lg-3]== 'J' || text[lg-3]== 'j' ) &&  (text[lg-2]== 'P' || text[lg-2]=='p' ) &&  (text[lg-1]== 'g' || text[lg-1]== 'G' ))
                                return TipeJPG;
    else if ( (text[lg-4]== 'J' || text[lg-4]== 'j' ) && (text[lg-3]== 'P' || text[lg-3]== 'p' ) &&  (text[lg-2]== 'E' || text[lg-2]=='e' ) &&  (text[lg-1]== 'g' || text[lg-1]== 'G' ))
                                return TipeJPG;

    return TypeImageInvalid;
 }
