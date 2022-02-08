#include "QrcalculateMask.h"

long getCondition3(char **,QR_Data *);
int getCondition4(char **,QR_Data *);
long getCondition2(char **,QR_Data *);
long getCondition1(char **,QR_Data *);

long getpointMask_micro_QR(char **_matrix,QR_Data *data)
{
    long sum1=0;
    long sum2=0;

    for(int i =1 ; i < data->num_modules ; i++)
    {
        if(_matrix[data->num_modules-1][i] == '1' )
        {
            sum1++;
        }
    }

    for(int i =1 ; i < data->num_modules ; i++)
    {
        if(_matrix[i][data->num_modules-1] == '1' )
        {
            sum2++;
        }
    }

    if(sum1 > sum2)
       sum1 = 16 * sum2 + sum1;
    else
       sum1 = 16 * sum1 + sum2;



    return sum1;
}


long getpointMask(char **_matrix,QR_Data *data)
{
    long total=0;

    total = getCondition3(_matrix,data);
    total=total + getCondition4(_matrix,data);
    total=total + getCondition2(_matrix,data);
    total=total + getCondition1(_matrix,data);

    return total;
}

long getCondition2(char **_matrix,QR_Data *data)
{
    long points = 0;
    for(int a =0 ; a < data->num_modules -1 ; a++)
    {
        for(int i =0 ; i < data->num_modules-1 ; i++)
        {
            if(_matrix[i][a] == '1' && _matrix[i+1][a] == '1'
                    &&_matrix[i][a+1] == '1' && _matrix[i+1][a+1] == '1' )
            {
                points=points + 3;

            }
            else  if(_matrix[i][a] == '0' && _matrix[i+1][a] == '0'
                     &&_matrix[i][a+1] == '0' && _matrix[i+1][a+1] == '0' )
            {
                points=points + 3;

            }
        }
    }



    return points;
}


long getCondition1(char **_matrix,QR_Data *data)
{
    long points = 0;


   for(int i =0 ; i < data->num_modules ; i++)
   {
      for(int a =0 ; a < data->num_modules-4 ; a++)
      {
             if(_matrix[i][a] == '1' && _matrix[i][a+1] == '1' &&_matrix[i][a+2] == '1'
                &&_matrix[i][a+3] == '1' &&_matrix[i][a+4] == '1' )
             {
                 points=points + 3;
                 a=a+5;

                 while(a < data->num_modules && _matrix[i][a++] == '1')
                    points=points + 1;

             }
             else  if(_matrix[i][a] == '0' && _matrix[i][a+1] == '0' &&_matrix[i][a+2] == '0'
                   &&_matrix[i][a+3] == '0' &&_matrix[i][a+4] == '0'  )
             {
                 points=points + 3;
                 a=a+5;

                 while(a < data->num_modules && _matrix[i][a++] == '0')
                      points=points + 1;

             }
      }
   }

   for(int a =0 ; a < data->num_modules ; a++)
   {
      for(int i =0 ; i < data->num_modules-4 ; i++)
      {
             if(_matrix[i][a] == '1' && _matrix[i+1][a] == '1' &&_matrix[i+2][a] == '1'
                &&_matrix[i+3][a] == '1' &&_matrix[i+4][a] == '1' )
             {
                 points=points + 3;
                 i=i+5;

                 while(i < data->num_modules && _matrix[i++][a] == '1')
                    points=points + 1;

             }
             else  if(_matrix[i][a] == '0' && _matrix[i+1][a] == '0' &&_matrix[i+2][a] == '0'
                   &&_matrix[i+3][a] == '0' &&_matrix[i+4][a] == '0'  )
             {
                 points=points + 3;
                 i=i+5;

                 while(i < data->num_modules && _matrix[i++][a] == '0')
                      points=points + 1;

             }
      }
   }


   return points;
}



long getCondition3(char **_matrix,QR_Data *data)
{
   long points = 0;

   for(int i =0 ; i < data->num_modules ; i++)
   {
      for(int a =0 ; a < data->num_modules-10 ; a++)
      {
             if(_matrix[i][a] == '1' && _matrix[i][a+1] == '0' &&_matrix[i][a+2] == '1'
                &&_matrix[i][a+3] == '1' &&_matrix[i][a+4] == '1' && _matrix[i][a+5] == '0' &&
                _matrix[i][a+6] == '1' && _matrix[i][a+7] == '0' && _matrix[i][a+8] == '0' &&
                  _matrix[i][a+9] == '0' && _matrix[i][a+10] == '0' )
             {
                 points=points + 40;
                 a=a+11;
             }
             else  if(_matrix[i][a] == '0' && _matrix[i][a+1] == '0' &&_matrix[i][a+2] == '0'
                   &&_matrix[i][a+3] == '0' &&_matrix[i][a+4] == '1' &&_matrix[i][a+5] == '0' &&
                  _matrix[i][a+6] == '1' && _matrix[i][a+7] == '1' && _matrix[i][a+8] == '1' &&
                  _matrix[i][a+9] == '0' && _matrix[i][a+10] == '1' )
             {
                 points=points + 40;
                 a=a+11;
             }
      }
   }


   for(int a =0 ; a < data->num_modules ; a++)
   {
      for(int i =0 ; i < data->num_modules-10 ; i++)
      {
             if(_matrix[i][a] == '1' && _matrix[i+1][a] == '0' &&_matrix[i+2][a] == '1'
                &&_matrix[i+3][a] == '1' &&_matrix[i+4][a] == '1' && _matrix[i+5][a] == '0' &&
                _matrix[i+6][a] == '1' && _matrix[i+7][a] == '0' && _matrix[i+8][a] == '0' &&
                  _matrix[i+9][a] == '0' && _matrix[i+10][a] == '0' )
             {
                 points=points + 40;
                 i=i+11;
             }
             else  if(_matrix[i][a] == '0' && _matrix[i+1][a] == '0' &&_matrix[i+2][a] == '0'
                   &&_matrix[i+3][a] == '0' &&_matrix[i+4][a] == '1' &&_matrix[i+5][a] == '0' &&
                  _matrix[i+6][a] == '1' && _matrix[i+7][a] == '1' && _matrix[i+8][a] == '1' &&
                  _matrix[i+9][a] == '0' && _matrix[i+10][a] == '1' )
             {
                 points=points + 40;
                 i=i+11;
             }
      }
   }


   return points;
}

int getCondition4(char **_matrix,QR_Data *data)
{
    long aux = 0;
    int aux2 =0 ;
    int aux3 ;
    float p;

    for(int i =0 ; i < data->num_modules ; i++)
    {
      for(int a =0 ; a < data->num_modules ; a++)
      {
             if( _matrix[i][a] == '1' )
             {
                aux ++;
             }
      }
    }

    p = aux / (float) (data->num_modules * data->num_modules);
    aux2 = 100*p;
    aux2 = aux2 / 5 ;
    aux3 = (aux2 +1 ) *5;
    aux2 = aux2  *5;

    aux3 = aux3 - 50;
    aux2 = aux2 - 50;

    if(aux3 < 0)
        aux3 = -1 * aux3;

    if(aux2 < 0)
        aux2 = -1 * aux2;

    aux3 = aux3 /5;
    aux2 = aux2 / 5;

    if(aux3 > aux2)
        return aux2 *10;
    else
        return aux3 *10;

}
