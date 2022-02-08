#include "QrMask.h"

  void setmask_0(char **,QR_Data *);
  void setmask_1(char **,QR_Data *);
  void setmask_2(char **,QR_Data *);
  void setmask_3(char **,QR_Data *);
  void setmask_4(char **,QR_Data *);
  void setmask_5(char **,QR_Data *);
  void setmask_6(char **,QR_Data *);
  void setmask_7(char **,QR_Data *);
  char ** getMaskMatrix_micro_QR(char **,char **,QR_Data *);
  char ** getMaskMatrix_QR(char **,char **,QR_Data *);


  char ** getMaskMatrix(char **matrix,char **functions_matrix,QR_Data *data)
  {
     if(data->isMicro == 1)
         return  getMaskMatrix_micro_QR(matrix,functions_matrix,data);
     else
         return getMaskMatrix_QR(matrix,functions_matrix,data);


    return 0;
  }


  char ** getMaskMatrix_micro_QR(char **matrix,char **functions_matrix,QR_Data *data)
  {
   long points[4];
   long max;
   char **mask1 = createMatrix(matrix,data);


   setmask_1(mask1,data);
   points[0] = getpointMask_micro_QR(mask1,data);
   max=points[0];


   copyMatrix(mask1,matrix,data);
   setmask_4(mask1,data);
   points[1] = getpointMask_micro_QR(mask1,data);

   if(max < points[1])
              max = points[1];


   copyMatrix(mask1,matrix,data);
   setmask_6(mask1,data);
   points[2] = getpointMask_micro_QR(mask1,data);

   if(max < points[2])
              max = points[2];

   copyMatrix(mask1,matrix,data);
   setmask_7(mask1,data);
   points[3] = getpointMask_micro_QR(mask1,data);

    if(max < points[3])
        max = points[3];

    for(int a=0; a<4; a++){
        if(points[a] == max)
        {
            data->mask = a;
            a=4;
        }
    }

  switch(data->mask)
  {
        case 0:
             copyMatrix(mask1,matrix,data);
             setmask_1(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
             data->mask=1;
        break;
        case 1:
             copyMatrix(mask1,matrix,data);
             setmask_4(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
             data->mask=4;
        break;
        case 2:
             copyMatrix(mask1,matrix,data);
             setmask_6(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
             data->mask=6;
        break;
        case 3:
             copyMatrix(mask1,matrix,data);
             setmask_7(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
             data->mask=7;
        break;
        default:

        break;

  }


    return mask1;
  }

char ** getMaskMatrix_QR(char **matrix,char **functions_matrix,QR_Data *data)
{
   long points[8];
   long min;
   char **mask1 = createMatrix(matrix,data);


   setmask_0(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[0] = getpointMask(mask1,data);
   min=points[0];

   copyMatrix(mask1,matrix,data);
   setmask_1(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[1] = getpointMask(mask1,data);


   if(min > points[1])
              min = points[1];


   copyMatrix(mask1,matrix,data);
   setmask_2(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[2] = getpointMask(mask1,data);


   if(min > points[2])
              min = points[2];


   copyMatrix(mask1,matrix,data);
   setmask_3(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[3] = getpointMask(mask1,data);


   if(min > points[3])
              min = points[3];


   copyMatrix(mask1,matrix,data);
   setmask_4(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[4] = getpointMask(mask1,data);


   if(min > points[4])
              min = points[4];



   copyMatrix(mask1,matrix,data);
   setmask_5(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[5] = getpointMask(mask1,data);


   if(min > points[5])
              min = points[5];


   copyMatrix(mask1,matrix,data);
   setmask_6(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[6] = getpointMask(mask1,data);


   if(min > points[6])
              min = points[6];


   copyMatrix(mask1,matrix,data);
   setmask_7(mask1,data);
   sumMatrix(mask1,functions_matrix,data);
   points[7] = getpointMask(mask1,data);

   if(min > points[7])
              min = points[7];


  for(int a=0;a<8;a++)
  {
      if(points[a] == min)
      {
         data->mask = a;
         a=8;
      }
  }



  switch(data->mask)
  {
        case 0:
             copyMatrix(mask1,matrix,data);
             setmask_0(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 1:
             copyMatrix(mask1,matrix,data);
             setmask_1(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 2:
             copyMatrix(mask1,matrix,data);
             setmask_2(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 3:
             copyMatrix(mask1,matrix,data);
             setmask_3(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 4:
             copyMatrix(mask1,matrix,data);
             setmask_4(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 5:
             copyMatrix(mask1,matrix,data);
             setmask_5(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        case 6:
             copyMatrix(mask1,matrix,data);
             setmask_6(mask1,data);
             sumMatrix(mask1,functions_matrix,data);
        break;
        default:

        break;

  }


   return mask1;
}

void setmask_0(char **matrix,QR_Data *data)
{
   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          if((i+a)  % 2 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}

void setmask_1(char **matrix,QR_Data *data)
{
   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          if(a % 2 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}

void setmask_2(char **matrix,QR_Data *data)
{
   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          if(i % 3 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}


void setmask_3(char **matrix,QR_Data *data)
{
   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          if((i+a)  % 3 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}

void setmask_4(char **matrix,QR_Data *data)
{
   int aux;
   int aux2;

   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          aux = a /2 ;
          aux2 = i / 3;


          if((aux+aux2)  % 2 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}

void setmask_5(char **matrix,QR_Data *data)
{
   long aux;
   int  aux2;

   for(int i =0 ; i < data->num_modules ; i++)
   {
      for(int a =0 ; a < data->num_modules ; a++)
      {
          aux = i * a  ;
          aux2 = aux % 2;
          if(aux2 == 0)
          {
             aux2 = aux % 3;
             if(aux2 == 0)
             {
               if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
               else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';
             }
          }

      }
   }
}

void setmask_6(char **matrix,QR_Data *data)
{
   long aux;
   int aux2;
   int aux3;

   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          aux = a * i ;
          aux2 = aux % 2;
          aux3 = aux % 3;

          if((aux3+aux2)  % 2 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}

void setmask_7(char **matrix,QR_Data *data)
{
   long aux;
   int aux2;
   int aux3;

   for(int i =0 ; i < data->num_modules ; i++)
   {

      for(int a =0 ; a < data->num_modules ; a++)
      {
          aux = a + i ;
          aux2 = aux % 2;
          aux = a * i ;
          aux3 = aux % 3;

          if((aux3+aux2)  % 2 == 0)
          {
             if (matrix[i][a] == '0')
                        matrix[i][a] = '1';
             else if (matrix[i][a] == '1')
                         matrix[i][a] = '0';

          }
      }
   }
}


