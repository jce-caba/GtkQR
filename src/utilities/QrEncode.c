#include "QrEncode.h"

char * encondeNumeric(const char *value)
{
  int aux,lg = strlen(value),totalsize=1;
  char c[4];
  char *bits4,*bits7,*bits10;
  char *res;

  res = (char *) malloc(sizeof(char));
  res[0] =  '\0';

  bits4 = (char*) malloc((4+1)* sizeof(char));
  bits4[4] = '\0';

  bits7 = (char*) malloc((7+1)* sizeof(char));
  bits7[7] = '\0';

  bits10 = (char*) malloc((10+1)* sizeof(char));
  bits10[10] = '\0';

  for (int i = 0; i < lg; i =i+ 3)
  {
       c[0]=value[i];
       if (i + 1 >= lg )
       {
            c[1] = '\0';
            aux = atoi(c);
            toBinary_n_bits(bits4,aux,4);
            totalsize = 4+totalsize;
            res = (char *) realloc(res, (totalsize)* sizeof(char));
            strcat(res, bits4);

       }
       else if (i + 2 >= lg )
       {
           c[1] = value[i+1];
           c[2] =  '\0';
           aux = atoi(c);

           // 7 binary bits
           toBinary_n_bits(bits7,aux,7);
           totalsize = 7+totalsize;
           res = (char *) realloc(res, (totalsize)* sizeof(char));
           strcat(res, bits7);
       }
       else
       {
           c[1] = value[i+1];
           c[2] = value[i+2];
           c[3] =  '\0';
           aux = atoi(c);

           // 10 binary bits
           toBinary_n_bits(bits10,aux,10);
           totalsize = 10+totalsize;
           res = (char *) realloc(res, (totalsize)* sizeof(char));
           strcat(res, bits10);


       }
  }

   free(bits4);
   free(bits7);
   free(bits10);

   return res;
}

char * encondeAlphaNumeric(const char *value)
{
  int aux,aux2,lg = strlen(value),totalsize=1;
  char c;
  char *bits6,*bits11;
  char *res;

  res = (char *) malloc(sizeof(char));
  res[0] =  '\0';

  bits6 = (char*) malloc((6+1)* sizeof(char));
  bits6[6] = '\0';

  bits11 = (char*) malloc((11+1)* sizeof(char));
  bits11[11] = '\0';



  for (int i = 0; i < lg; i =i+ 2)
  {
     c=value[i];
     aux = getAlphaNumericValue(c);

     if (i + 1 >= lg )
     {
        toBinary_n_bits(bits6,aux,6);
        totalsize = 6+totalsize;
        res = (char *) realloc(res, (totalsize)* sizeof(char));
        strcat(res, bits6);

     }
     else
     {
        c = value[i+1];
        aux2 = getAlphaNumericValue(c);
        aux =(aux*45) + aux2;

        toBinary_n_bits(bits11,aux,11);
        totalsize = 11+totalsize;
        res = (char *) realloc(res, (totalsize)* sizeof(char));
        strcat(res, bits11);

     }

  }

   free(bits6);
   free(bits11);


  return res;
}


int  getAlphaNumericValue(char txt)
{
  int value=1;

  if( (int) txt >= 48 && (int) txt <= 57 )
  {
     value=(int) txt;
     value=value-48;
  }
  else if( (int) txt >= 65 && (int) txt <= 90 )
  {
     value=(int) txt;
     value=value - 55;
  }
  else if( (int) txt == 32  )
        value = 36;
  else if( (int) txt == 36  )
        value = 37;
  else if( (int) txt == 37  )
        value = 38;
  else if( (int) txt == 42  )
        value = 39;
  else if( (int) txt == 43  )
        value = 40;
  else if( (int) txt == 45  )
        value = 41;
  else if( (int) txt == 46  )
        value = 42;
  else if( (int) txt == 47  )
        value = 43;
  else if( (int) txt == 58  )
        value = 44;

  return value;
}

char * encondeISO_8859_1(int *value,int num_bytes)
{
    char *res ;
    char *num ;

    if(value == NULL)
                 return NULL;

    res = (char *) malloc((num_bytes*8 + 1) *sizeof(char));
    res[0] =  '\0';

    num = (char*) malloc(9* sizeof(char));
    num[8] = '\0';


    for (int i =0 ; i < num_bytes;i ++)
    {
        toBinary_n_bits(num,value[i],8);
        strcat(res, num);
    }


    free(num);

    return res;
}

char * encondeKanji(int *value,int num_bytes)
{
  int aux,aux2,totalsize=1;
  char *bits13,*bits8,*bits16;
  char *res;
  int i = 0;

  res = (char *) malloc(sizeof(char));
  res[0] =  '\0';

  bits13 = (char*) malloc((13+1)* sizeof(char));
  bits13[13] = '\0';

  bits8 = (char*) malloc((8+1)* sizeof(char));
  bits8[8] = '\0';

  bits16 = (char*) malloc((16+1)* sizeof(char));
  bits16[16] = '\0';

  while (i < num_bytes)
  {
     aux=value[i];
     i++;

     if (aux >=33088 && aux <= 40956) //range 0x8140 to 0x9FFC
     {
       aux=aux -33088 ;
       toBinary_n_bits(bits16,aux,16);
       least_significant_byte(bits16,bits8);
       aux = toDecimal(bits8);

       most_significant_byte(bits16,bits8);
       aux2 = toDecimal(bits8);

       aux2 = 192 * aux2;
       aux = aux + aux2;

       toBinary_n_bits(bits13,aux,13);

       totalsize = 13 + totalsize;
       res = (char *) realloc(res, (totalsize)* sizeof(char));
       strcat(res, bits13);


     }
     else if (aux >=57408 && aux <= 60351) //0xE040 to 0xEBBF
     {
        aux=aux -49472 ;
        toBinary_n_bits(bits16,aux,16);
        least_significant_byte(bits16,bits8);
        aux2 = toDecimal(bits8);

        most_significant_byte(bits16,bits8);
        aux = toDecimal(bits8);

        aux = 192 * aux;
        aux = aux + aux2;

        toBinary_n_bits(bits13,aux,13);
        totalsize = 13 + totalsize;
        res = (char *) realloc(res, (totalsize)* sizeof(char));
        strcat(res, bits13);

     }

  }

   free(bits13);
   free(bits8);
   free(bits16);


  return res;
}
