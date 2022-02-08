#include "QrMatrixFunction.h"

char ** getMatrixFunction_micro_QR(QR_Data *);
char ** getMatrixFunction_QR(QR_Data *);

void setMatrixFunctionFormat_micro_QR(char **,QR_Data *,const char *);
void setMatrixFunctionFormat_QR(char **,QR_Data *,const char *);


char ** getMatrixFunction(QR_Data *data)
{
   if(data->isMicro == 1)
        return getMatrixFunction_micro_QR (data);
    else
        return getMatrixFunction_QR (data);
}

char ** getMatrixFunction_micro_QR(QR_Data *data)
{
   char **matrix = (char **) malloc(  (data->num_modules+1)* sizeof(char *));

   for(int i =0 ; i < data->num_modules ; i++)
   {
      matrix[i] = (char *) malloc((data->num_modules + 1)* sizeof(char));
      for(int a =0 ; a < data->num_modules ; a++)
                                    matrix[i][a] = '0';

      matrix[i][data->num_modules] = '\0';
   }

   matrix[data->num_modules]=  NULL;

    /* finder patterns */
    matrix[0][0] = '1';matrix[1][0] = '1';matrix[2][0] = '1';matrix[3][0] = '1';matrix[4][0] = '1';matrix[5][0] = '1';matrix[6][0] = '1';
    matrix[0][6] = '1';matrix[1][6] = '1';matrix[2][6] = '1';matrix[3][6] = '1';matrix[4][6] = '1';matrix[5][6] = '1';matrix[6][6] = '1';
    matrix[0][1] = '1'; matrix[0][2] = '1';matrix[0][3] = '1';matrix[0][4] = '1'; matrix[0][5] = '1';
    matrix[6][1] = '1'; matrix[6][2] = '1';matrix[6][3] = '1';matrix[6][4] = '1'; matrix[6][5] = '1';
    matrix[2][2] = '1'; matrix[3][2] = '1'; matrix[4][2] = '1';
    matrix[2][3] = '1'; matrix[3][3] = '1'; matrix[4][3] = '1';
    matrix[2][4] = '1'; matrix[3][4] = '1'; matrix[4][4] = '1';

    for(int i =8 ; i < data->num_modules ; i=i+2)
                                   matrix[0][i] = '1';

    for(int i =8 ; i < data->num_modules ; i=i+2)
                                   matrix[i][0] = '1';


 return matrix;
}


char ** getMatrixFunction_QR(QR_Data *data)
{
   char **matrix;
   int aux;

   matrix = (char **) malloc(  (data->num_modules+1)* sizeof(char *));

   for(int i =0 ; i < data->num_modules ; i++)
   {
      matrix[i] = (char *) malloc((data->num_modules + 1)* sizeof(char));
      for(int a =0 ; a < data->num_modules ; a++)
                                    matrix[i][a] = '0';

      matrix[i][data->num_modules] = '\0';
   }

    matrix[data->num_modules]=  NULL;


    /* finder patterns */
    matrix[0][0] = '1';matrix[1][0] = '1';matrix[2][0] = '1';matrix[3][0] = '1';matrix[4][0] = '1';matrix[5][0] = '1';matrix[6][0] = '1';
    matrix[0][6] = '1';matrix[1][6] = '1';matrix[2][6] = '1';matrix[3][6] = '1';matrix[4][6] = '1';matrix[5][6] = '1';matrix[6][6] = '1';
    matrix[0][1] = '1'; matrix[0][2] = '1';matrix[0][3] = '1';matrix[0][4] = '1'; matrix[0][5] = '1';
    matrix[6][1] = '1'; matrix[6][2] = '1';matrix[6][3] = '1';matrix[6][4] = '1'; matrix[6][5] = '1';
    matrix[2][2] = '1'; matrix[3][2] = '1'; matrix[4][2] = '1';
    matrix[2][3] = '1'; matrix[3][3] = '1'; matrix[4][3] = '1';
    matrix[2][4] = '1'; matrix[3][4] = '1'; matrix[4][4] = '1';

    aux = data->num_modules-1;
    matrix[0][aux] = '1';matrix[1][aux] = '1';matrix[2][aux] = '1';matrix[3][aux] = '1';matrix[4][aux] = '1';matrix[5][aux] = '1';matrix[6][aux] = '1';
    matrix[0][aux - 1] = '1'; matrix[0][aux -2] = '1';matrix[0][aux -3] = '1';matrix[0][aux -4] = '1'; matrix[0][aux -5] = '1';
    matrix[6][aux - 1] = '1'; matrix[6][aux -2] = '1';matrix[6][aux -3] = '1';matrix[6][aux -4] = '1'; matrix[6][aux -5] = '1';
    matrix[aux][1] = '1'; matrix[aux][2] = '1';matrix[aux][3] = '1';matrix[aux][4] = '1'; matrix[aux][5] = '1';
    aux = data->num_modules-5;
    matrix[2][aux] = '1'; matrix[3][aux] = '1'; matrix[4][aux] = '1';
    aux = data->num_modules-4;
    matrix[2][aux] = '1'; matrix[3][aux] = '1'; matrix[4][aux] = '1';
    aux = data->num_modules-3;
    matrix[2][aux] = '1'; matrix[3][aux] = '1'; matrix[4][aux] = '1';

    aux = data->num_modules-7;
    matrix[0][aux] = '1';matrix[1][aux] = '1';matrix[2][aux] = '1';matrix[3][aux] = '1';matrix[4][aux] = '1';matrix[5][aux] = '1';matrix[6][aux] = '1';
    matrix[aux][0] = '1';matrix[aux+1][0] = '1';matrix[aux+2][0] = '1';matrix[aux+3][0] = '1';matrix[aux+4][0] = '1';matrix[aux+5][0] = '1';matrix[aux+6][0] = '1';
    matrix[aux][6] = '1';matrix[aux+1][6] = '1';matrix[aux+2][6] = '1';matrix[aux+3][6] = '1';matrix[aux+4][6] = '1';matrix[aux+5][6] = '1';matrix[aux+6][6] = '1';
    matrix[aux][1] = '1'; matrix[aux][2] = '1'; matrix[aux][3] = '1';matrix[aux][4] = '1'; matrix[aux][5] = '1';
    aux = aux + 2 ;
    matrix[aux][2] = '1'; matrix[aux+1][2] = '1'; matrix[aux+2][2] = '1';
    matrix[aux][3] = '1'; matrix[aux+1][3] = '1'; matrix[aux+2][3] = '1';
    matrix[aux][4] = '1'; matrix[aux+1][4] = '1'; matrix[aux+2][4] = '1';

    /* Timing Patterns */

    aux =  data->num_modules - 16 ;

    for (int i = 8 ; i < 8 + aux ; i =i +2 )
                  matrix[i][6] = '1';

    for (int i = 8 ; i < 8 + aux ; i =i +2 )
                  matrix[6][i] = '1';


     /* Dark Module */
     matrix[8][data->num_modules-8] = '1';


   return matrix;
}

void setMatrixFunctionFormat(char **matrix,QR_Data *data,const char * text)
{
   if(data->isMicro == 1)
         setMatrixFunctionFormat_micro_QR (matrix,data,text);
    else
         setMatrixFunctionFormat_QR (matrix,data,text);

}

void setMatrixFunctionFormat_micro_QR(char **matrix,QR_Data *data,const char * text)
{
    int b = 0;
    int lg =strlen(text) -1;

    if(lg < 0)
        return;



    for(int a=1 ; a < 9 ; a ++)
    {
        matrix[a][8] = text[b];
        b++;
    }

    for(int a=1 ; a < 8 ; a ++)
    {
        matrix[8][a] = text[lg];
        lg--;
    }


}

void setMatrixFunctionFormat_QR(char **matrix,QR_Data *data,const char * text)
{
     int b = 0;

     if(text == NULL)
               return;

     for(int a=0 ; a < 9 ; a ++)
     {
         if( a != 6)
         {
           matrix[a][8] = text[b];
           b++;
         }
     }

     for(int a=7 ; a >=0 ; a --)
     {
         if( a != 6)
         {
           matrix[8][a] = text[b];
           b++;
         }
     }

     b = 0;

     for(int a=data->num_modules - 1 ; a >= data->num_modules - 7 ; a --)
     {
           matrix[8][a] = text[b];
           b++;
     }

     for(int a=data->num_modules - 8 ; a <= data->num_modules - 1 ; a ++)
     {
           matrix[a][8] = text[b];
           b++;
     }

}

void setMatrixFunctionVersion(char **matrix,QR_Data *data,const char * text)
{
    int lg ;
    int b ;
    int aux  ;

    lg = strlen(text) - 1;
    b = lg;

    aux = data->num_modules-11;

    for(int i=0 ; i < 6 ; i ++)
    {
        for(int a=0 ; a < 3 ; a ++)
        {
          matrix[i][aux+a] = text[b];
          b -- ;
        }
    }


     b = lg;

    for(int i=0 ; i < 6 ; i ++)
    {
        for(int a=0 ; a < 3 ; a ++)
        {
           matrix[aux+a][i] = text[b];
           b -- ;
        }
    }
}

