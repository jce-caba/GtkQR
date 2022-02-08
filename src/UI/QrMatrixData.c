#include "QrMatrixData.h"

  typedef struct  {

     char **matrix;
     const char *word;
     int counter;
     int CoordX;
     int CoordY;
     int limitY;

     short must_up;

  } __Dates;

 char ** getMatrixData_micro_QR(QR_Data *,const char *);
 char ** getMatrixData_QR(QR_Data *,const char *);

 void setmatrix_1(__Dates *,int);
 void setmatrix_2_6(__Dates *,int,int);
 void setmatrix_N(__Dates *,int,int);



 int upwardPlacement(__Dates *);
 int downwardPlacement(__Dates *);
 int upwardPlacementonecolumn(__Dates *);
 int downPlacementonecolumn(__Dates *);

 int bounceUp(__Dates *  ,int,int,int);
 int bounceDown(__Dates *  ,int,int,int);
 int totalUp(__Dates *,int,int);
 int totalDown(__Dates *,int,int);

 int cornerUp(__Dates *,int);

 int stepUp(__Dates *,int*,int,int);
 int stepDown(__Dates *,int*,int,int);

 int upper_right_version(__Dates *,int);

 int stepUp_left_step (__Dates * ,int*,int,int);
 int stepDown_left_step (__Dates *,int*,int,int);

 int up_to_information(__Dates *,int,int *,int);

 int totalUp_until (__Dates *,int,int);
 int totalDown_until (__Dates *,int,int);


char ** getMatrixData(QR_Data *data,const char * text)
{
    if(data->isMicro == 1)
        return getMatrixData_micro_QR (data,text);
    else
        return getMatrixData_QR (data,text);

}

char ** getMatrixData_micro_QR(QR_Data *data,const char * text)
{
   char **matrix;
   __Dates _dates;

   matrix = (char **) malloc(  (data->num_modules+1)* sizeof(char *));

   for(int i =0 ; i < data->num_modules ; i++)
   {
      matrix[i] = (char *) malloc((data->num_modules + 1)* sizeof(char));
      for(int a =0 ; a < data->num_modules ; a++)
                                    matrix[i][a] = 'n';

      matrix[i][data->num_modules] = '\0';
   }

    matrix[data->num_modules]=  NULL;

     _dates.matrix=matrix;
     _dates.counter=0;
     _dates.word=text;
     _dates.CoordX = data->num_modules-1;
     _dates.CoordY = data->num_modules-1;

    switch(data->qrversion)
    {
        case GTKQR_VERSION_M1:
               if (bounceUp(&_dates,1,data->num_modules-1,1)==0)
                          return matrix;

                _dates.CoordY = 9;
               bounceDown(&_dates,9,data->num_modules-1,4);

        break;
        case GTKQR_VERSION_M2:
               if (bounceUp(&_dates,1,data->num_modules-1,2)==0)
                          return matrix;
               bounceUp(&_dates,9,data->num_modules-1,4);

        break;
        case GTKQR_VERSION_M3:
               if (bounceUp(&_dates,1,data->num_modules-1,3)==0)
                          return matrix;

                _dates.CoordY = 9;
               bounceDown(&_dates,9,data->num_modules-1,4);


        break;
        case GTKQR_VERSION_M4:
               if (bounceUp(&_dates,1,data->num_modules-1,4)==0)
                          return matrix;
               bounceUp(&_dates,9,data->num_modules-1,4);
        break;
    default:

        break;
    }

    return matrix;

}



char ** getMatrixData_QR(QR_Data *data,const char * text)
{
   char **matrix;
   __Dates _dates;
   int aux;

   matrix = (char **) malloc(  (data->num_modules+1)* sizeof(char *));

   for(int i =0 ; i < data->num_modules ; i++)
   {
      matrix[i] = (char *) malloc((data->num_modules + 1)* sizeof(char));
      for(int a =0 ; a < data->num_modules ; a++)
                                    matrix[i][a] = 'n';

      matrix[i][data->num_modules] = '\0';
   }

    matrix[data->num_modules]=  NULL;


     _dates.matrix=matrix;
     _dates.counter=0;
     _dates.word=text;



    switch(data->qrversion_number)
    {
        case 1:
              setmatrix_1(&_dates,data->num_modules);
        break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
              aux = 3 + 2 * (data->qrversion_number -2);
              setmatrix_2_6(&_dates,data->num_modules,aux);
        break;
        default:
              setmatrix_N(&_dates,data->num_modules,data->qrversion_number);
            break;
    }





    return matrix;
}

void setmatrix_1(__Dates * data,int num_modules)
{
     data->CoordX = num_modules-1;
     data->CoordY = num_modules-1;

     if (bounceUp(data,9,num_modules-1,4)==0)
           return;

     if (totalUp(data,num_modules,2)==0)
           return;

     if (cornerUp(data,num_modules)==0)
           return;


     bounceDown(data,9,num_modules-9,3);
}

void setmatrix_2_6(__Dates * data,int num_modules,int parameter)
{
     int c[1];
     data->CoordX = num_modules-1;
     data->CoordY = num_modules-1;
     c[0]= num_modules-4;

    if (bounceUp(data,9,num_modules-1,2)==0)
           return;

    if (stepUp(data,c,1,9)==0)
            return;

    if  (stepDown(data,c,1,num_modules)  == 0)
            return ;

    if  (stepUp_left_step(data,c,1,0)  == 0)
                    return ;


    if(totalDown(data,num_modules,parameter)==0)
            return;


    if (cornerUp(data,num_modules)==0)
           return;

    bounceDown(data,9,num_modules-9,3);

  
}



void setmatrix_N(__Dates *data,int num_modules,int version)
{
     int total_elements;
     int *c;
     data->CoordX = num_modules-1;
     data->CoordY = num_modules-1;

     total_elements = getNumberElements(version);

     c = (int *) malloc((total_elements)* sizeof(int));
     getSeparation(version ,c);

     if  (up_to_information(data,num_modules,c,total_elements-1)  == 0)
                   goto finish;

     data ->must_up=1;


    for(int i= 1; i < total_elements ; i ++)
    {
        if(data ->must_up==1)
        {
            if(totalUp_until(data,num_modules,c[i])==0)
                goto finish;
        }
        else
        {
            if(totalDown_until(data,num_modules,c[i])==0)
               goto finish;
        }

        if(data ->must_up==1 && i !=total_elements-1)
        {
            if (stepUp(data,c,total_elements,0)==0)
                goto finish;

            if (stepDown(data,c,total_elements,num_modules)==0)
                goto finish;

            if  (stepUp_left_step(data,c,total_elements,0)  == 0)
                goto finish;

            data ->must_up=0;
        }
        else if(i !=total_elements-1)
        {
            if (stepDown(data,c,total_elements,num_modules)==0)
                goto finish;

            if (stepUp(data,c,total_elements,0)==0)
                goto finish;

            if  (stepDown_left_step(data,c,total_elements,num_modules)  == 0)
                goto finish;


            data ->must_up=1;
        }
    }


    for(int i=0;i<total_elements-2;i++)
                     c[i]= c[i+1];


    if(data ->must_up==1)
    {
        data->CoordY = num_modules-9;
        if (stepUp(data,c,total_elements-2,9)==0)
                        goto finish;

        data->CoordX=data->CoordX-1;
        if  (stepDown(data,c,total_elements-2,num_modules-11)  == 0)
                    goto finish;

        bounceUp(data,9,num_modules-11,2);
    }

finish:

    free(c);
}

int upwardPlacement(__Dates * data)
{
   while(data->CoordY >= data->limitY)
   {
      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX][data->CoordY] = data->word[data->counter];
      data->counter ++;

      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX -1 ][data->CoordY] =data->word[data->counter];
      data->counter ++;
      data->CoordY--;
   }
   data->CoordY++;
   return 1;
}

int downwardPlacement(__Dates * data)
{
   while(data->CoordY <= data->limitY)
   {
      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX][data->CoordY] =data->word[data->counter];
      data->counter ++;

      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX -1 ][data->CoordY] =data->word[data->counter];
      data->counter ++;
      data->CoordY++;
   }
   data->CoordY--;
   return 1;
}

int upwardPlacementonecolumn(__Dates * data)
{
   while(data->CoordY >= data->limitY)
   {
      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX][data->CoordY] = data->word[data->counter];
      data->counter ++;
      data->CoordY--;
   }
   data->CoordY++;
   return 1;
}

int downPlacementonecolumn(__Dates * data)
{
   while(data->CoordY <= data->limitY)
   {
      if (data->word[data->counter] == '\0')
                       return 0;

      data->matrix[data->CoordX][data->CoordY] = data->word[data->counter];
      data->counter ++;
      data->CoordY++;
   }
   data->CoordY--;
   return 1;
}



int bounceUp(__Dates *  data,int Y_Upper,int Ylower,int bounce_number)
{
    // Empieza subiendo y va rebotando en Y_Upper y Ylower
    //
    int a = 0;

    while (a < bounce_number)
    {
       data->limitY = Y_Upper;
       if (upwardPlacement(data)==0)
            return 0;

       a++;

       data->CoordX=data->CoordX-2;
       if(a < bounce_number)
       {
         data->limitY = Ylower;
         if (downwardPlacement(data)==0)
                     return 0;

         data->CoordX=data->CoordX-2;
         a++;
       }
    }
  return 1;
}

int bounceDown(__Dates *  data,int Y_Upper,int Ylower,int bounce_number)
{
    // Empieza bajando y va rebotando en Y_Upper y Ylower
    //

    int a = 0;

    while (a < bounce_number)
    {
       data->limitY = Ylower;
       if (downwardPlacement(data)==0)
            return 0;

       a++;

       data->CoordX=data->CoordX-2;
       if(a < bounce_number)
       {
         data->limitY = Y_Upper;
         if (upwardPlacement(data)==0)
                     return 0;

         data->CoordX=data->CoordX-2;
         a++;
       }
    }
  return 1;
}

int totalUp(__Dates *  data,int num_modules,int bounce_number)
{
    // Empieza desde  data->CoordY  , hasta arriba  y vuelve a bajar
    // salta linea

    int a = 0;

    while (a < bounce_number)
    {
       data->limitY = 7;

       if (upwardPlacement(data)==0)
                     return 0;

       data->limitY = 0;
       data->CoordY = 5;

       if (upwardPlacement(data)==0)
                     return 0;

       a++;

       data->CoordX=data->CoordX-2;
       if(a < bounce_number)
       {
         data->limitY = 5;
         if (downwardPlacement(data)==0)
                     return 0;

         data->CoordY = 7;
         data->limitY = num_modules-1;
         if (downwardPlacement(data)==0)
                     return 0;


         data->CoordX=data->CoordX-2;
         a++;
       }
    }
  return 1;

}

int totalDown(__Dates *  data,int num_modules,int bounce_number)
{
    // Empieza desde  data->CoordY  , hasta abajo  y vuelve a subir
    // salta linea


    if (bounce_number > 0)
    {
       data->limitY = 5;

       if (downwardPlacement(data)==0)
                     return 0;

       data->limitY = num_modules -1;
       data->CoordY = 7;

       if (downwardPlacement(data)==0)
                     return 0;

       data->CoordX=data->CoordX-2;
       if (bounce_number > 1)
       {
           return totalUp(data,num_modules,bounce_number-1);
       }
    }
  return 1;

}



int cornerUp(__Dates *  data,int num_modules)
{
  // Esquina antes timing
   data->CoordY = num_modules-9;
   data->limitY = 9;

   if (upwardPlacement(data)==0)
                     return 0;


   data->CoordX=data->CoordX-3;
   return 1;
}

int stepUp(__Dates *  data,int* steps,int num_steps,int Y_Upper)
{
    // una colimna arriba saltandoe scalonees hasta Y_Upper

    data->limitY = steps[0];

    for(int i=0;i < num_steps;i++)
    {
       if (upwardPlacement(data)==0)
                    return 0;

       data->CoordY = data->CoordY - 6;
       if (i  + 1 < num_steps)
       {
           data->limitY = steps[i+1];
       }
    }

    if(Y_Upper <=5 && data->CoordY >=7)
    {
        data->limitY = 7;
        if (upwardPlacement(data)==0)
                     return 0;

        data->CoordY = 5;
        data->limitY =Y_Upper;

        if (upwardPlacement(data)==0)
                     return 0;
    }
    else
    {
        data->limitY =Y_Upper;

        if (upwardPlacement(data)==0)
                     return 0;

    }

    data->CoordX=data->CoordX-2;
    return 1;
}

int stepDown(__Dates *  data,int* steps,int num_steps,int num_modules)
{
    // una colimna arriba saltandoe scalonees hasta abajo
    int aux;

    aux = steps[num_steps -1 ] - 6 ;

    if (data->CoordY <= 5  && aux >= 7 )
    {
        data->limitY =5;

        if (downwardPlacement(data)==0)
                     return 0;

        data->CoordY = 7;
    }

    data->limitY = aux ;

    for(int i=num_steps -1 ;i >= 0;i--)
    {
        if (downwardPlacement(data)==0)
                     return 0;

         data->CoordY = data->CoordY + 6;
         if (i  - 1 >= 0)
         {
           data->limitY = steps[ i -1 ] - 6 ;
         }

    }

    data->limitY =num_modules -1;

    if (downwardPlacement(data)==0)
                     return 0;

    data->CoordX=data->CoordX-2;
    return 1;
}

int stepUp_left_step (__Dates *  data,int* steps,int num_steps,int Y_Upper)
{
    // una columna arriba bordeando escalon por la izquierda
    int aux;
    data->limitY = steps[0];


    for(int i=0;i < num_steps;i++)
    {
       if (upwardPlacement(data)==0)
                    return 0;

       data->CoordX=data->CoordX-1;
       data->CoordY --;


       if(data->limitY-5 <=5 && data->CoordY >=7 )
       {
           aux = data->limitY-5;
           data->limitY = 7;
           if (upwardPlacementonecolumn(data)==0)
                     return 0;

           data->CoordY = 5;
           data->limitY = aux;

           if (upwardPlacementonecolumn(data)==0)
                     return 0;


           data->CoordX++;
           data->CoordY --;

       }
       else
       {
           data->limitY = data->limitY-5;
           if (upwardPlacementonecolumn(data)==0)
                     return 0;

           data->CoordX++;
           data->CoordY --;
       }



       if (i  + 1 < num_steps)
       {
           data->limitY = steps[i+1];
       }
    }

     if(Y_Upper <=5 && data->CoordY >=7)
     {
        data->limitY = 7;
        if (upwardPlacement(data)==0)
                     return 0;

        data->CoordY = 5;
        data->limitY =Y_Upper;

        if (upwardPlacement(data)==0)
                     return 0;

     }
     else
     {
        data->limitY =Y_Upper;

        if (upwardPlacement(data)==0)
                     return 0;
     }


    data->CoordX=data->CoordX-2;
    return 1;
}

int stepDown_left_step (__Dates *  data,int* steps,int num_steps,int num_modules)
{
    // una columna abajo bordeando escalon por la izquierda
    int aux;

    data->limitY = steps[num_steps -1 ] - 6 ;


    for(int i=num_steps -1 ;i >= 0;i--)
    {
        if (downwardPlacement(data)==0)
                     return 0;


        if(data->limitY + 6 >=7 && data->CoordY <=5 )
        {
             data->CoordX--;
             data->CoordY ++;

             aux = data->limitY + 5;
             data->limitY = 5;
             if (downPlacementonecolumn(data)==0)
                     return 0;

             data->CoordY = 7;
             data->limitY = aux;

             if (downPlacementonecolumn(data)==0)
                     return 0;

              data->CoordX++;
              data->CoordY ++;
        }
        else
        {
           data->CoordX--;
           data->CoordY ++;
           data->limitY = data->limitY + 5;

           if (downPlacementonecolumn(data)==0)
                     return 0;

           data->CoordX++;
           data->CoordY ++;
        }

         if (i  - 1 >= 0)
         {
           data->limitY = steps[ i -1 ] - 6 ;
         }

    }

    data->limitY =num_modules -1;

    if (downwardPlacement(data)==0)
                     return 0;

    data->CoordX=data->CoordX-2;

    return 1;
}

int upper_right_version(__Dates *  data,int num_modules)
{
    data->CoordX=data->CoordX-1;
    data->CoordY =0;
    data->limitY = 5;

    if (downPlacementonecolumn(data)==0)
                     return 0;

    data->CoordX=data->CoordX+1;
    data->CoordY =7;
    data->limitY = num_modules-1;
    if (downwardPlacement(data)==0)
                     return 0;

   data->CoordX=data->CoordX-2;
   return 1;
}

 int up_to_information(__Dates *data,int num_modules,int *obstacle ,int num_obstacle)
 {
    if (bounceUp(data,9,num_modules-1,2)==0)
           return 0;

    if (stepUp(data,obstacle,num_obstacle,9)==0)
            return 0;




    if (stepDown(data,obstacle,num_obstacle,num_modules)==0)
            return 0;

    if  (stepUp_left_step(data,obstacle,num_obstacle,7)  == 0)
                        return 0;


    if  (upper_right_version(data,num_modules)  == 0)
            return 0;

    return 1;
 }

 int totalUp_until (__Dates *  data,int num_modules,int X_limit)
{
  int number = data->CoordX - X_limit + 2;
  number =number / 2;

  if(totalUp(data,num_modules,number)==0)
            return 0;

  if(number % 2==0)
       data->must_up =1;
  else
       data->must_up =0;

  return 1;

}

 int totalDown_until (__Dates *  data,int num_modules,int X_limit)
{
  int number = data->CoordX - X_limit + 2;
  number =number / 2;

  if(totalDown(data,num_modules,number)==0)
            return 0;

  if(number % 2==0)
       data->must_up =0;
  else
       data->must_up =1;

  return 1;

}


