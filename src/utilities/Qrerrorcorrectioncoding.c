#include "Qrerrorcorrectioncoding.h"

char ** _getgroups_all_versions(const char *,QR_Data *);
char ** _getgroups_especial(const char *,QR_Data *);

char *  getfinalmessage_special(const char *,char *** group1,QR_Data *data);
char *  getfinalmessage_all_versions(char *** group1,char *** group2,QR_Data *data);

int   countarray(int *);

int *  getErrorCorrectionCodewords(char **,QR_Data *);
int * multiplier(int *, int,int);
int *  discardfirstterm (int *,int);

void xor(int,int *,int *);
void multiply(int,int,int *,int *);
int *  copyarray (int *,int);

 char *getfinalmessage_all_versions(char *** group1,char *** group2,QR_Data *data)
 {
    int numBlocks1;
    int sizeBlocks1;

    int numBlocks2;
    int sizeBlocks2;

    int total;
    int *ref;

    char **txt;
    char *interleaved_data;
    char *interleaved_data_error;
    int b = 0;

    int ** codeworderrorgroup1;
    int ** codeworderrorgroup2 = NULL;

    char * w;
    char * w2;


    numBlocks1 = getNumberBlocks1 (data);
    sizeBlocks1 = getNumberDataBlocks1 (data);



    numBlocks2 = getNumberBlocks2 (data);
    sizeBlocks2 = getNumberDataBlocks2 (data);


    if(sizeBlocks1 >= sizeBlocks2)
               total = sizeBlocks1;
    else
               total = sizeBlocks2 ;

    interleaved_data = (char *) malloc((8*numBlocks1*sizeBlocks1 + 8*numBlocks2*sizeBlocks2 + 1)* sizeof(char));
    interleaved_data[0]=  '\0';


    while( b < total)
    {
        for(int i=0 ; i<numBlocks1; i++)
        {
            txt = group1[i];

            if (b < sizeBlocks1)
                   strcat(interleaved_data, txt[b]);
        }
        for(int i=0 ; i<numBlocks2; i++)
        {
            txt = group2[i];
            if (b < sizeBlocks2)
                      strcat(interleaved_data, txt[b]);
        }

        b++;
    }



    // calculate error correction codewords
    codeworderrorgroup1 = (int **) malloc(  numBlocks1* sizeof(int *));

    for(int i=0 ; i<numBlocks1; i++)
    {
        txt = group1[i];
        codeworderrorgroup1[i] = getErrorCorrectionCodewords(txt,data);
    }


    if (numBlocks2 > 0)
          codeworderrorgroup2 = (int **) malloc(  numBlocks2* sizeof(int *));

    for(int i=0 ; i<numBlocks2; i++)
    {
        txt = group2[i];
        codeworderrorgroup2[i] = getErrorCorrectionCodewords(txt,data);
    }



    // Interleave the Error Correction Codewords
    // all codeword have same total

    total = countarray(codeworderrorgroup1[0]);
    b = 0;

    interleaved_data_error = (char *) malloc((8*numBlocks1*total + 8*numBlocks2*total + 1)* sizeof(char));
    interleaved_data_error[0]=  '\0';

    w = (char*) malloc(9* sizeof(char));
    w[8] = '\0';

    while( b < total)
    {
        for(int i=0 ; i<numBlocks1; i++)
        {
            ref = codeworderrorgroup1[i];
            toBinary_n_bits(w,ref[b],8);
            strcat(interleaved_data_error, w);
        }
        for(int i=0 ; i<numBlocks2; i++)
        {
            ref = codeworderrorgroup2[i];
            toBinary_n_bits(w,ref[b],8);
            strcat(interleaved_data_error, w);
        }

        b++;
    }

    free(w);

    // delete memory
    for(int i=0 ; i<numBlocks1; i++)
    {
        free(codeworderrorgroup1[i]) ;
    }
    free(codeworderrorgroup1) ;

    for(int i=0 ; i<numBlocks2; i++)
    {
        free(codeworderrorgroup2[i]) ;
    }

    if (numBlocks2 > 0)
         free(codeworderrorgroup2) ;


    numBlocks1 = strlen(interleaved_data);
    numBlocks2 = strlen(interleaved_data_error);

    total = getremainderbits(data->qrversion_number);
    w = (char *) malloc((numBlocks1 + numBlocks2 + total +1)* sizeof(char));
    w[0]=  '\0';



    strcat(w, interleaved_data);
    free(interleaved_data);
    strcat(w, interleaved_data_error);
    free(interleaved_data_error);



    if (total == 0)
    {

       return w;
    }
    else
    {
        w2 = (char *) malloc((total +1)* sizeof(char));
        w2[0]=  '\0';

        for(int i=0; i<total; i++)
            strcat(w2, "0");

        strcat(w,w2);
        free(w2);


        return w;
    }
 }

 char *** getgroup1(char ** value,QR_Data *data) // // * CHECK OK * //
 {
    int numBlocks1;
    int sizeBlocks1;
    char *** group1;
    int counter=0,counter2=0;

    numBlocks1 = getNumberBlocks1 (data);
    sizeBlocks1 = getNumberDataBlocks1 (data);

    group1 = (char ***) malloc(  (numBlocks1+1)* sizeof(char **));
    for(int i=0 ; i<numBlocks1;i++)
    {
        group1[i] = (char **) malloc( (sizeBlocks1+1) *  sizeof(char *));
        counter=0;
        for (int a = 0 ; a< sizeBlocks1; a++)
        {
            group1[i][a]= value[counter2];
            counter++;
            counter2++;
        }
        group1[i][counter]=NULL;

    }


    group1[numBlocks1]=  NULL;

    return group1;

 }


 char *** getgroup2(char **value,QR_Data *data)// // * CHECK OK * //
 {
    int numBlocks2;
    int sizeBlocks2;
    int aux;
    char *** group2;
    int counter=0,counter2=0;

    numBlocks2 = getNumberBlocks2 (data);
    if(numBlocks2 == 0)
          return NULL;

    sizeBlocks2 = getNumberDataBlocks2 (data);

    aux = getNumberBlocks1 (data);
    counter2 = getNumberDataBlocks1 (data);
    counter2 = aux * counter2 ;


    group2 = (char ***) malloc(  (numBlocks2+1)* sizeof(char **));
    for(int i=0 ; i<numBlocks2;i++)
    {
        group2[i] = (char **) malloc( (sizeBlocks2+1) *  sizeof(char *));
        counter=0;
        for (int a = 0 ; a< sizeBlocks2; a++)
        {
            group2[i][a]= value[counter2];
            counter++;
            counter2++;
        }
        group2[i][counter]=NULL;

    }


    group2[numBlocks2]=  NULL;

    return group2;
 }

 char ** _getgroups(const char *value,QR_Data *data)
 {
     if(data->qrversion == GTKQR_VERSION_M1 && data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_NOTHING )
              return _getgroups_especial(value,data);
     else if (data->qrversion == GTKQR_VERSION_M3){
        if(data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_LOW)
            return _getgroups_especial(value,data);

        else if(data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM)
            return _getgroups_especial(value,data);

     }

    return  _getgroups_all_versions(value,data);
 }

 char ** _getgroups_especial(const char *value,QR_Data *data){ // // * CHECK OK * //
     int aux,lg = strlen(value);
     char ** groups;
     int a=0;


    aux=(lg+4)/8;
    groups = (char **) malloc(  (aux+1)* sizeof(char *));

        for(int i=0; i<aux; i++)
        {
            groups[i] = (char *) malloc( (9)* sizeof(char));
            if( i== aux -1 )
            {
                groups[i][0]='0';
                groups[i][1]='0';
                groups[i][2]='0';
                groups[i][3]='0';
                groups[i][4]=value[a];
                groups[i][5]=value[a + 1 ];
                groups[i][6]=value[a + 2];
                groups[i][7]=value[a + 3];
            }
            else
            {
                groups[i][0]=value[a];
                groups[i][1]=value[a + 1];
                groups[i][2]=value[a + 2];
                groups[i][3]=value[a + 3];
                groups[i][4]=value[a + 4];
                groups[i][5]=value[a + 5 ];
                groups[i][6]=value[a + 6];
                groups[i][7]=value[a + 7];
            }

            groups[i][8]='\0';
            a=a+8;
        }




     groups[aux] = (char *) malloc(sizeof(char));
     groups[aux][0]=  '\0';



     return groups;
 }

 char ** _getgroups_all_versions(const char *value,QR_Data *data){ // // * CHECK OK * //
     int aux,lg = strlen(value);
     char ** groups;
     int a=0;


    aux=lg/8;
    groups = (char **) malloc(  (aux+1)* sizeof(char *));

        for(int i=0; i<aux; i++)
        {
            groups[i] = (char *) malloc( (9)* sizeof(char));
            groups[i][0]=value[a];
            groups[i][1]=value[a + 1];
            groups[i][2]=value[a + 2];
            groups[i][3]=value[a + 3];
            groups[i][4]=value[a + 4];
            groups[i][5]=value[a + 5 ];
            groups[i][6]=value[a + 6];
            groups[i][7]=value[a + 7];
            groups[i][8]='\0';
            a=a+8;
        }




     groups[aux] = (char *) malloc(sizeof(char));
     groups[aux][0]=  '\0';



     return groups;
 }

 void  freememory (char **value){
    int a=0;
    char * v;
    char c=2;

    if (value == NULL)
                 return;

    while ( c != '\0' )
    {
      c =value[a][0];
      v = value[a];
      free(v);
      v = NULL;
      a ++;
    }

    free(value);

 }

 void  freememorygroup (char ***value){
    int a=0;
    char ** v;

    if (value == NULL)
                 return;

    v= value[a];

    while ( v != NULL )
    {
      free(v);
      a ++;
      v= value[a];
    }
    free(v);
    free(value);

 }


 int *  getErrorCorrectionCodewords(char **allblocks,QR_Data *data)
 {
    int codewordsPerBlock;
    int aux =0;
    int aux2;
    int total;
    int *generatorpolynomial;
    int *messagepolynomial;
    int *multiplier ;
    int *copymultiplier;

    codewordsPerBlock = getECCodewords (data);
    generatorpolynomial = getGeneratorPolynomial(codewordsPerBlock) ;


    while (allblocks[aux] !=  NULL)
    {
        aux++;
    }


    messagepolynomial = toDecimalarray(aux,allblocks);

    //multiply the message polynomial by x to n , codewordsPerBlock is n (10)
    total = aux + codewordsPerBlock ;
    messagepolynomial = (int *) realloc(messagepolynomial, (total)* sizeof(int));
    for (int i = aux ; i < total; i =i + 1)
                 messagepolynomial[i] = -1;


    //The lead term of the generator polynomial should also have the same exponent, so multiply by x15 to get
    //    codewordsPerBlock = 10 aux = 16

    generatorpolynomial = (int *) realloc(generatorpolynomial, (total)* sizeof(int));
    for (int i = codewordsPerBlock + 1 ; i < total; i =i + 1)
                 generatorpolynomial[i] = -1;


    //The number of steps in the division must equal the number of terms in the message polynomial
    //  In this case, the division will take 16 steps to complete  aux = 16

    multiplier = copyarray (messagepolynomial,total);
    copymultiplier = copyarray (messagepolynomial,total);

    for(int i =0 ;i < aux ;i ++)
    {
        //Step 1a:  Multiply the Generator Polynomial by the Lead Term of the Message Polynomial
         //Step Na: Multiply the Generator Polynomial by the Lead Term of the XOR result from the previous step
        aux2 = getLog(multiplier[0]);
        multiply(total,aux2,generatorpolynomial,multiplier);

        //Step 1b: XOR the result with the message polynomial
        //Step Nb: XOR the result with the result from step 1b
        xor(total,copymultiplier,multiplier);
        multiplier = discardfirstterm (multiplier,total);
        total --;
        free(copymultiplier);
        copymultiplier = copyarray (multiplier,total);

    }

    // add -1
    multiplier = (int *) realloc(multiplier, (total+1)* sizeof(int));
    multiplier[total] = -1;

    free(generatorpolynomial);
    free(messagepolynomial);
    free(copymultiplier);

    return multiplier;
 }

  int *  discardfirstterm (int *value,int lg)
  {
      int *res;
      res = (int *) malloc( (lg - 1) *  sizeof(int ));

      for (int i = 0 ; i < lg -1 ; i =i + 1)
      {
        res[i] = value[i+1];

      }


      free(value);
      return res;
  }

  int *  copyarray (int *value,int lg)
  {
      int *res;
      res = (int *) malloc( lg *  sizeof(int ));

      for (int i = 0 ; i < lg  ; i =i + 1)
      {
        res[i] = value[i];

      }

      return res;
  }



void xor(int total,int * messagepolynomial,int * multiplier)
{

    for (int i = 0 ; i < total; i =i + 1)
    {
        if (messagepolynomial[i]==-1 && multiplier[i] ==-1)
            multiplier[i] = -1;
        else
        {
            if (messagepolynomial[i]==-1 )
                         messagepolynomial[i] = 0;

            if (multiplier[i] ==-1)
                         multiplier[i] = 0;


            multiplier[i] = messagepolynomial[i]  ^ multiplier[i];
        }

    }

}

void multiply(int total,int mp,int * generatorpolynomial,int * multiplier)
{
    for (int i = 0 ; i < total; i =i + 1)
    {
        if(generatorpolynomial[i]==-1)
            multiplier[i] = -1;
        else
        {
            multiplier[i] = mp + generatorpolynomial[i] ;
            multiplier[i] = getIntegerNotation(multiplier[i]);
        }
    }

}




 int   countarray(int *value)
 {
     int ret = 0;

     while(value[ret] != -1)
        ret ++ ;

     return ret;
 }

 char *getfinalmessage(const char *text,char *** group1,char *** group2,QR_Data *data)
 {
     if(data->qrversion == GTKQR_VERSION_M1 && data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_NOTHING )
              return getfinalmessage_special(text,group1,data);
     else if (data->qrversion == GTKQR_VERSION_M3){
        if(data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_LOW)
              return getfinalmessage_special(text,group1,data);

        else if(data->correction_level==GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM)
            return getfinalmessage_special(text,group1,data);

     }

    return  getfinalmessage_all_versions(group1,group2,data);
 }




 char *getfinalmessage_special(const char *text,char *** group1,QR_Data *data)
 {
    int *ref;
    int total;

    char *interleaved_data_error;
    int ** codeworderrorgroup1;

    char * w;


    // calculate error correction codewords
    codeworderrorgroup1 = (int **) malloc( sizeof(int *));
    codeworderrorgroup1[0] = getErrorCorrectionCodewords(group1[0],data);

    // Interleave the Error Correction Codewords
    // all codeword have same total

    total = countarray(codeworderrorgroup1[0]);


    interleaved_data_error = (char *) malloc((8*total  + 1)* sizeof(char));
    interleaved_data_error[0]=  '\0';

    w = (char*) malloc(9* sizeof(char));
    w[8] = '\0';
    ref = codeworderrorgroup1[0];

    for(int i=0 ; i<total; i++)
    {
      toBinary_n_bits(w,ref[i],8);
      strcat(interleaved_data_error, w);
    }
    free(w);

    // delete memory
    free(codeworderrorgroup1[0]);
    free(codeworderrorgroup1) ;


    total = strlen(text) + 8*total;

    w = (char *) malloc((total +1)* sizeof(char));
    w[0]=  '\0';

    strcat(w, text);
    strcat(w, interleaved_data_error);
    free(interleaved_data_error);



    return w;
 }

