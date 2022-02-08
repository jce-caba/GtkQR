#include "QrDrawData.h"

 void drawgrid(cairo_t *cr,Draw_Data *container)
 {
   double aux = 0;

#if GTK_CHECK_VERSION(3,0,0)
    gdk_cairo_set_source_rgba (cr, &container->black);
#else
    cairo_set_source_rgb(cr, container->black.red, container->black.green,container->black.blue);
#endif

    cairo_set_line_width (cr, 1);
    cairo_move_to(cr , container->startX , container->startY );

   while ( aux < container->width)
   {
       cairo_line_to (cr,container->startX + container->width,container->startY + aux);
       aux = aux + container->size_modules;
       cairo_move_to(cr , container->startX , container->startY + aux);

   }

   aux = 0;
   cairo_move_to(cr , container->startX , container->startY );

   while ( aux < container->width)
   {
       cairo_line_to (cr,container->startX + aux,container->startY + container->width);
       aux = aux + container->size_modules;
       cairo_move_to(cr , container->startX + aux, container->startY );

   }

   cairo_stroke(cr);

 }

 void drawData(cairo_t *cr,Draw_Data *container,char **matrix)
 {
    int a =0;
    int i= 0;

    if(matrix==NULL)
        return;

#if GTK_CHECK_VERSION(3,0,0)
    gdk_cairo_set_source_rgba (cr, &container->black);
#else
    cairo_set_source_rgb(cr, container->black.red, container->black.green,container->black.blue);
#endif

    do
    {
        do
        {
             if(matrix[a][i] == '1')
             {
                 cairo_rectangle (cr, container->startX + container->size_modules*a, container->startY + container->size_modules* i, container->size_modules, container->size_modules);
             }

         i++;
        }while(matrix[a][i] != '\0');

       i=0;
       a++;

    }while(matrix[a] !=NULL);
    cairo_fill (cr);

 }
