#include "QrMatrixUtils.h"

void sumMatrix(char **matrix1,char **matrix2,QR_Data *data)
{
   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          if(matrix1[i][a] == '1' ||  matrix2[i][a]== '1')
                                          matrix1[i][a]= '1';
          else
                                          matrix1[i][a]= '0';

      }
   }


}

char ** createMatrix(char **matrix,QR_Data *data)
{
   char **_copy;


   _copy = (char **) malloc(  (data->num_modules+1)* sizeof(char *));

   for(int i =0 ; i < data->num_modules ; i++)
   {
      _copy[i] = (char *) malloc((data->num_modules + 1)* sizeof(char));
      for(int a =0 ; a < data->num_modules ; a++)
                                    _copy[i][a] = matrix[i][a];

      _copy[i][data->num_modules] = '\0';
   }

    _copy[data->num_modules]=  NULL;


    return _copy;
}


void copyMatrix(char **matrix1,char **matrix2,QR_Data *data)
{

   for(int i =0 ; i < data->num_modules ; i++)
   {
      for(int a =0 ; a < data->num_modules ; a++)
                                    matrix1[i][a] = matrix2[i][a];

   }

}

void freeMatrix(char **matrix)
{
   int a =0;

   do
   {
     free(matrix[a]);
     a++;
   }while(matrix[a] !=NULL);

   free(matrix);

}
