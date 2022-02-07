#ifndef QRDRAWDATA_H_INCLUDED
#define QRDRAWDATA_H_INCLUDED
#include <gtk/gtk.h>

  typedef struct  {

  #if GTK_CHECK_VERSION(3,0,0)
     GdkRGBA white;
     GdkRGBA black;
  #else
     GdkColor white;
     GdkColor black;
  #endif

     double size_modules;
     guint startX, startY;
     guint width;

 } Draw_Data;




 void drawData(cairo_t *,Draw_Data *,char **);

#endif // QRDRAWDATA_H_INCLUDED
