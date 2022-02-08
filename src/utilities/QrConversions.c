#include "QrConversions.h"



 char * toBinary(int value){ // * CHECK OK * //
  char ar[100];
  int i=0;
  char *ret;

  while (value!=0)
  {
    if (value % 2 ==0)
      ar[i]='0';
    else
      ar[i]='1';

    value = value/2 ;
    i++;
  }

  if(i>0)
  {
      ret = (char*) malloc((i+1)* sizeof(char));

      for(int a =i-1;a>=0;a--)
      {
        ret[i-a-1]=ar[a];
      }

      ret[i] = '\0';
      return ret;
  }
  else
  {
      ret = (char*) malloc(2* sizeof(char));
      ret[0]='0';ret[1] = '\0';
      return ret;
  }

 }

 char * fillzeros(int lg,char *value){ // * CHECK OK * //
     int oldlg;
     char *ret;
     int i=0;

     if(value!=NULL && strlen(value) < lg)
     {
        oldlg =  strlen(value);
        ret = (char*) malloc((lg+1)* sizeof(char));

        for(int a =0;a<lg;a++)
            ret[a] = '0';

        ret[lg] = '\0';

        for(int a =lg-oldlg;a<lg;a++)
        {
            ret[a]=value[i];
            i++;
        }

        return ret;
     }
     else
     {
         oldlg =  strlen(value);
         ret = (char*) malloc((oldlg+1)* sizeof(char));
         for(int a =0;a<oldlg;a++)
              ret[a] = value[a];

         ret[oldlg] = '\0';
         return ret;
     }


 }

 char * fillzerosafter(int lg,char *value){ // * CHECK OK * //

     int oldlg;
     char *ret;

     if(value!=NULL && strlen(value) < lg)
     {
        oldlg =  strlen(value);
        ret = (char*) malloc((lg+1)* sizeof(char));

        for(int a =0;a<lg;a++)
        {
            if(a<oldlg)
                ret[a]=value[a];
            else
                ret[a] = '0';
        }

        ret[lg] = '\0';

        return ret;
     }
     else
     {
         oldlg =  strlen(value);
         ret = (char*) malloc((oldlg+1)* sizeof(char));
         strcpy (ret,value);
         ret[oldlg] = '\0';
         return ret;
     }

 }

 void least_significant_byte(char * value,char * result) // // * CHECK OK * //
 {
   int a =0;


   for (int i = 8 ; i < 16; i =i + 1)
   {
     result[a]=value[i];
     a=a+1;
   }

 }

 void most_significant_byte(char *value,char * result) // // * CHECK OK * //
 {

   for (int i = 0; i < 8; i =i+ 1)
   {
      result[i]=value[i];
   }

 }

 int toDecimal(char *value) // // * CHECK OK * //
 {
   int exp=0,lg = strlen(value),res=0,aux;

   for (int i = lg -1 ; i >= 0; i =i - 1)
   {
     aux=value[i];

     if(aux == 49)
     {
        aux = (int) pow (2,exp);
        res =res + aux;
     }

     exp++;
   }

   return res;
 }

 int* toDecimalarray(int lg,char **value) // // * CHECK OK * //
 {
   int aux;
   int *res;

   res = (int *) malloc(  lg* sizeof(int));


   for (int i = 0 ; i < lg; i =i + 1)
   {
     aux = toDecimal(value[i]);
     res[i] = aux;
   }

   return res;
 }



 void toBinary_n_bits(char *text,int value,int num_bits){
  int i=0;
  int a = num_bits-1;

  for(int i=0;i<num_bits;i++)
                       text[i]='0';


  while (value!=0)
  {
    if (value % 2 !=0)
             text[a]='1';

    value = value/2 ;
    i++;
    a--;
  }

 }

 char * number_to_char(int value)
 {
     int count=0;
     int digit=value;
     char c;
     char *ret;

     while(digit>0)
     {
       digit=digit/10;
       count++;
     }

     ret = (char*) malloc((count+1)* sizeof(char));
     ret[count] = '\0';

     for(int i = 0 ; i < count ; i++)
     {
         digit=value % 10;
         value=value/10;

         switch(digit)
         {
             case 0:
                 c ='0';
             break;
             case 1:
                 c ='1';
             break;
             case 2:
                 c ='2';
             break;
             case 3:
                 c ='3';
             break;
             case 4:
                 c ='4';
             break;
             case 5:
                 c ='5';
             break;
             case 6:
                 c ='6';
             break;
             case 7:
                 c ='7';
             break;
             case 8:
                 c ='8';
             break;
             case 9:
                 c ='9';
             break;
             default:
                 c ='0';
             break;
         }
         ret[count-1-i] = c;

     }



     return ret;
 }
