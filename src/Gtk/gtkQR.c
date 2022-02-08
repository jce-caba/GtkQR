#include <gtkQR.h>
#include <string.h>
#include "QrProcesses.h"
#include "QrDrawData.h"
#include "QrMatrixUtils.h"
#include "QrDataAnalysis.h"
#include "QrConversions.h"

    #if GTK_CHECK_VERSION(4,0,0)

    #else
      #define __NO_GTK4
    #endif


    


enum
{
    P_0, /*  */
    QR_TEXT,
    QR_CORRECTION,
    PADDING
};

/* Private data structure */
struct _GtkQRPrivate
{

    Draw_Data draw_data;
    QR_Data data;

    float margin;
    gboolean draw_image;
    gboolean save_text;
    char *text;
    char **matrix;

    short order_draw;
    short dynamic_margin;
    short extra_margin;

    #if GTK_CHECK_VERSION(4,0,0)
      GdkSurface *window;
    #else
      GdkWindow *window;
    #endif


};



/* Internal API */
static void gtk_qr_set_property(GObject *object, guint prop_id,
                                const GValue *value, GParamSpec *pspec);
static void gtk_qr_get_property(GObject *object, guint prop_id,
                                GValue *value, GParamSpec *pspec);



    #ifdef __NO_GTK4 
    static void gtk_qr_realize(GtkWidget *widget);
    #endif



static void clear_variables(GtkQRPrivate *);
static void set_text(GtkQRPrivate *,const char *,gboolean);
static GType Error_Correction_Level_get_type ();
static void draworder(GtkQR *);

#if GTK_CHECK_VERSION(4,0,0)
static void gtk_qr_snapshot (GtkWidget *widget, GtkSnapshot *snapshot);
static void gtk_qr_unrealize (GtkWidget *);
#elif GTK_CHECK_VERSION(3,0,0)
static void gtk_qr_destroy (GtkWidget *);
static gboolean gtk_qr_draw (GtkWidget *widget, cairo_t *cr);
#else
static void gtk_qr_unrealize (GtkWidget *);
static gboolean gtk_qr_expose(GtkWidget *,GdkEventExpose *);
#endif



/* Define type */
G_DEFINE_TYPE_WITH_CODE (GtkQR, gtk_qr, GTK_TYPE_WIDGET, G_ADD_PRIVATE (GtkQR))


#define parent_class gtk_qr_parent_class

/* Initialization */
static void gtk_qr_class_init(GtkQRClass *klass)
{

    GObjectClass *g_class;
    GtkWidgetClass *w_class;
    GParamSpec *pspec;
    GType Error_Correction_Level_TYPE;

    g_class = G_OBJECT_CLASS(klass);
    w_class = GTK_WIDGET_CLASS(klass);

    /* Override widget class methods */
    g_class->set_property  = gtk_qr_set_property;
    g_class->get_property  = gtk_qr_get_property;

    #ifdef __NO_GTK4 
    w_class->realize       = gtk_qr_realize;
    #endif

#if GTK_CHECK_VERSION(4,0,0)
    w_class->snapshot  = gtk_qr_snapshot;
    w_class->unrealize  = gtk_qr_unrealize;
#elif GTK_CHECK_VERSION(3,0,0)
    w_class->draw  = gtk_qr_draw;
    w_class->destroy  = gtk_qr_destroy;
#else
    w_class->expose_event  = gtk_qr_expose;
    w_class->unrealize  = gtk_qr_unrealize;
#endif

    /* Install property */

    pspec =g_param_spec_string ("qrtext","QRtext","The text of qr","",
                                G_PARAM_STATIC_STRINGS | G_PARAM_READABLE | G_PARAM_WRITABLE);

    g_object_class_install_property(g_class, QR_TEXT, pspec);

    Error_Correction_Level_TYPE = Error_Correction_Level_get_type ();

    pspec = g_param_spec_enum ("qrcorrection","QR_CORRECTION",
                               "The correction of qr", Error_Correction_Level_TYPE,GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM,G_PARAM_READWRITE);

    g_object_class_install_property(g_class, QR_CORRECTION, pspec);


}

static void gtk_qr_init(GtkQR *_qr)
{

    GtkQRPrivate *priv;

    priv = gtk_qr_get_instance_private (_qr);
    //gtk_widget_set_has_window(GTK_WIDGET(_qr), TRUE);

    /* Set default values */
    priv->text = NULL;
    priv->data.isMicro = 0;
    priv->data.enable_UTF8 = 1;
    priv->draw_image = 0;
    priv->save_text = 1;
    priv->data.mask = 4;
    priv->order_draw = 0;

    priv->dynamic_margin = 1;
    priv->extra_margin = 0;

    priv->data.eci_mode = NULL;

    priv->matrix =NULL;
    priv->data.qrversion_number = GTKQR_NO_VERSION;
    priv->data.qrversion = GTKQR_VERSION_QR_NULL;
    priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM;
    /* Create cache for faster access */
    _qr->priv = priv;


#if GTK_CHECK_VERSION(3,0,0)
    gdk_rgba_parse (&priv->draw_data.white, "white");
    gdk_rgba_parse (&priv->draw_data.black, "black");
#else
    gdk_color_parse ( "white", &priv->draw_data.white);
    gdk_color_parse ( "black", &priv->draw_data.black);
#endif




}

/* Overriden virtual methods */
static void gtk_qr_set_property(GObject *object, guint prop_id,
                                const GValue *value, GParamSpec *pspec)
{

    GtkQR *_qr = GTK_QR(object);
    const gchar *txt;
    gint aux;


    switch(prop_id)
    {

    case QR_TEXT:
        txt = g_value_get_string (value);
        set_text(_qr->priv,txt,TRUE);
        break;
    case QR_CORRECTION:
        aux = g_value_get_enum(value);

        if(aux==0)
            _qr->priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_LOW;
        else  if(aux==1)
            _qr->priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM;
        else  if(aux==2)
            _qr->priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_QUALITY;
        else  if(aux==3)
            _qr->priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_HIGH;
        else  if(aux==4)
            _qr->priv->data.correction_level = GTKQR_ERROR_CORRECTION_LEVEL_NOTHING;


        break;
    default:

        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void gtk_qr_get_property(GObject *object, guint prop_id,
                                GValue *value, GParamSpec *pspec)
{

    GtkQR *_qr = GTK_QR(object);

    switch(prop_id)
    {

    case QR_TEXT:
        g_value_set_string(value, _qr->priv->text);
        break;
    case QR_CORRECTION:

        if(_qr->priv->data.correction_level == GTKQR_ERROR_CORRECTION_LEVEL_LOW)
            g_value_set_enum(value,0);
        else if(_qr->priv->data.correction_level == GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM)
            g_value_set_enum(value,1);
        else if(_qr->priv->data.correction_level == GTKQR_ERROR_CORRECTION_LEVEL_QUALITY)
            g_value_set_enum(value,2);
        else if(_qr->priv->data.correction_level == GTKQR_ERROR_CORRECTION_LEVEL_HIGH)
            g_value_set_enum(value,3);
        else if(_qr->priv->data.correction_level == GTKQR_ERROR_CORRECTION_LEVEL_NOTHING)
            g_value_set_enum(value,4);

        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

#ifdef __NO_GTK4
static void gtk_qr_realize(GtkWidget *widget)
{

    GtkQRPrivate *priv = GTK_QR(widget)->priv;
    GtkAllocation alloc;
    GdkWindowAttr attrs;
    guint attrs_mask;

    gtk_widget_set_realized(widget, TRUE);

    gtk_widget_get_allocation(widget, &alloc);

    attrs.x           = alloc.x;
    attrs.y           = alloc.y;
    attrs.width       = alloc.width;
    attrs.height      = alloc.height;
    attrs.window_type = GDK_WINDOW_CHILD;
    attrs.wclass      = GDK_INPUT_OUTPUT;
    attrs.event_mask  = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK ;

    attrs_mask = GDK_WA_X | GDK_WA_Y;

    priv->window = gdk_window_new(gtk_widget_get_parent_window(widget),
                                  &attrs, attrs_mask);
    gdk_window_set_user_data(priv->window, widget);
    gtk_widget_set_window(widget, priv->window);

    #if GTK_CHECK_VERSION(3,0,0)

    #else
    // gtk_style_set_background(widget->style, priv->window, GTK_STATE_NORMAL);
    #endif


}

#endif



#if GTK_CHECK_VERSION(4,0,0)
static void gtk_qr_unrealize (GtkWidget *widget)
{
    GtkQR *_qr = GTK_QR(widget);

    clear_variables(_qr->priv);


    if ( _qr->priv->text != NULL)
    {
        free(_qr->priv->text);
        _qr->priv->text =NULL;
    }

    GTK_WIDGET_CLASS (parent_class)->unrealize (widget);
}
#elif GTK_CHECK_VERSION(3,0,0)
static void gtk_qr_destroy (GtkWidget *widget)
{
    GtkQR *_qr = GTK_QR(widget);

    clear_variables(_qr->priv);


    if ( _qr->priv->text != NULL)
    {
        free(_qr->priv->text);
        _qr->priv->text =NULL;
    }

    GTK_WIDGET_CLASS (parent_class)->destroy (widget);
}
#else
static void gtk_qr_unrealize (GtkWidget *widget)
{
    GtkQR *_qr = GTK_QR(widget);
    clear_variables(_qr->priv);

    if ( _qr->priv->text != NULL)
    {
        free(_qr->priv->text);
        _qr->priv->text =NULL;
    }


    GTK_WIDGET_CLASS (parent_class)->unrealize (widget);
}

#endif


#if GTK_CHECK_VERSION(4,0,0)
void gtk_qr_snapshot (GtkWidget *widget, GtkSnapshot *snapshot)
{
  cairo_t* cairo;
  GtkQRPrivate *priv = GTK_QR(widget)->priv;
  GtkAllocation allocation;
  guint width, height;
  guint width_real, height_real;

  gtk_widget_get_allocation (widget, &allocation);
  cairo = gtk_snapshot_append_cairo (snapshot,&GRAPHENE_RECT_INIT (0, 0,allocation.width,allocation.height));

    width = allocation.width;
    height = allocation.height;

    gdk_cairo_set_source_rgba (cairo, &priv->draw_data.white);
    cairo_rectangle (cairo, 0, 0, width, height);
    cairo_fill (cairo);

    if (! priv->draw_image)
                return FALSE;

    if(width > height)
    {
        height_real = priv->margin * height;
        width_real =  height_real;
    }
    else
    {

        height_real = priv->margin * width;
        width_real =  height_real;
    }

    priv->draw_data.size_modules = width_real / (double) priv->data.num_modules;
    priv->draw_data.startX = (width - width_real) /2 ;
    priv->draw_data.startY = (height - height_real) /2 ;
    priv->draw_data.width = width_real ;

    drawData(cairo,&priv->draw_data,priv->matrix);
    cairo_destroy (cairo);
}
#elif GTK_CHECK_VERSION(3,0,0)
static gboolean gtk_qr_draw (GtkWidget *widget, cairo_t *cr)
{
    GtkQRPrivate *priv = GTK_QR(widget)->priv;
    guint width, height;
    guint width_real, height_real;

    priv->order_draw= 0;
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    gdk_cairo_set_source_rgba (cr, &priv->draw_data.white);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill (cr);

    if (! priv->draw_image)
                return FALSE;

    if(width > height)
    {
        height_real = priv->margin * height;
        width_real =  height_real;
    }
    else
    {

        height_real = priv->margin * width;
        width_real =  height_real;
    }

    priv->draw_data.size_modules = width_real / (double) priv->data.num_modules;
    priv->draw_data.startX = (width - width_real) /2 ;
    priv->draw_data.startY = (height - height_real) /2 ;
    priv->draw_data.width = width_real ;

    drawData(cr,&priv->draw_data,priv->matrix);

    return FALSE;
}

#else

static gboolean gtk_qr_expose(GtkWidget *widget,GdkEventExpose *event)
{
    GtkQRPrivate *priv = GTK_QR(widget)->priv;
    GtkAllocation alloc;
    guint width, height;
    guint width_real, height_real;

    cairo_t *cr;
    cr = gdk_cairo_create(event->window);

    priv->order_draw= 0;
    gtk_widget_get_allocation(widget, &alloc);

    width = alloc.width;
    height = alloc.height;

    cairo_set_source_rgb(cr, priv->draw_data.white.red, priv->draw_data.white.green,priv->draw_data.white.blue);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill (cr);


    if (! priv->draw_image)
        return FALSE;

    if(width > height)
    {
        height_real = priv->margin * height;
        width_real =  height_real;
    }
    else
    {

        height_real = priv->margin * width;
        width_real =  height_real;
    }

    priv->draw_data.size_modules = width_real / (double) priv->data.num_modules;
    priv->draw_data.startX = (width - width_real) /2 ;
    priv->draw_data.startY = (height - height_real) /2 ;
    priv->draw_data.width = width_real ;

    drawData(cr,&priv->draw_data,priv->matrix);

    cairo_destroy(cr);

    return TRUE;
}

#endif


/* Public API */
GtkWidget *gtk_qr_new(void)
{

    return(g_object_new(GTK_TYPE_QR, NULL));
}
GtkWidget *gtk_qr_new_with_text(const char * txt)
{
    if(txt==NULL)
        return g_object_new(GTK_TYPE_QR,NULL);

    else
        return g_object_new(GTK_TYPE_QR,"qrtext",txt, NULL);
}

GtkWidget *gtk_qr_new_with_text_and_correction(const char * txt,GtkQRErrorCorrectionLevel correction)
{
    if(txt==NULL)
        return g_object_new(GTK_TYPE_QR,"qrcorrection",correction, NULL);
    else
        return g_object_new(GTK_TYPE_QR,"qrcorrection",correction,"qrtext",txt, NULL);
}


GType Error_Correction_Level_get_type (void)
{
    static GType type = 0;

    static const GEnumValue my_enum_values[] =
    {
        { 0,"L","L" },
        { 1,"M","M" },
        { 2,"Q","Q" },
        { 3,"H","H" },
        { 4,"Nothing","Nothing" }
    };

    if (type == 0)
    {

        type = g_enum_register_static ("correction", my_enum_values);

    }
    return type;
}

GtkQRErrorCorrectionLevel gtk_qr_get_correction(GtkQR *_qr)
{

    g_return_val_if_fail(GTK_IS_QR(_qr), 0);

    return(_qr->priv->data.correction_level);
}

const char * gtk_qr_get_text(GtkQR *_qr)
{
    const char *txt;
    g_return_val_if_fail(GTK_IS_QR(_qr), 0);

    txt = _qr->priv->text;

    if ( txt == NULL)
        return "";
    else
        return(_qr->priv->text);
}

void gtk_qr_set_text(GtkQR *_qr,const char *txt)
{

    if(GTK_IS_QR(_qr) && txt != NULL)
    {
        g_object_set (G_OBJECT (_qr),"qrtext",txt,NULL);
        draworder(_qr);
    }
}


static void clear_variables(GtkQRPrivate *priv)
{
    if ( priv->matrix != NULL)
    {
        freeMatrix(priv->matrix);
        priv->matrix = NULL;
    }

    if ( priv->data.eci_mode != NULL)
    {
        free(priv->data.eci_mode);
        priv->data.eci_mode = NULL;
    }


}

void gtk_qr_set_text_and_correction(GtkQR *_qr,const char *txt,GtkQRErrorCorrectionLevel correction)
{
    if(GTK_IS_QR(_qr) && txt != NULL)
    {
        g_object_set (G_OBJECT (_qr),"qrcorrection",correction,"qrtext",txt,NULL);
        draworder(_qr);
    }
}

static void set_text(GtkQRPrivate *priv,const char *txt,gboolean copytexy)
{
    int value;
    clear_variables(priv);

    priv->matrix = calculateMatrix(txt,&priv->data);

    if(priv->matrix == NULL )
        priv->draw_image =FALSE;
    else
        priv->draw_image =TRUE;


    if(priv->save_text && copytexy)
    {
        if ( priv->text != NULL)
            free(priv->text);

        value = strlen(txt);
        priv->text = (char*) malloc((value+1)* sizeof(char));
        strcpy ( priv->text, txt);
        priv->text[value] =  '\0';
    }
    else  if(! priv->save_text && priv->text != NULL)
    {
        free(priv->text);
        priv->text =NULL;
    }

    if (priv->dynamic_margin)
        priv->margin = (float)priv->data.num_modules / (priv->data.num_modules + 8 + priv->extra_margin);
    else
        priv->margin = 0.72413f;

}

#if GTK_CHECK_VERSION(3,0,0)
void gtk_qr_set_background_color(GtkQR *_qr,GdkRGBA *color)
{
    if(GTK_IS_QR(_qr) && color !=NULL )
    {
        _qr->priv->draw_data.white= *color;
    }
}

void gtk_qr_set_foreground_color(GtkQR *_qr,GdkRGBA *color)
{
    if(GTK_IS_QR(_qr) && color !=NULL)
    {
        _qr->priv->draw_data.black= *color;
    }
}
#else
void gtk_qr_set_background_color(GtkQR *_qr,GdkColor *color)
{
    if(GTK_IS_QR(_qr) && color !=NULL )
    {
        _qr->priv->draw_data.white= *color;
    }
}

void gtk_qr_set_foreground_color(GtkQR *_qr,GdkColor *color)
{
    if(GTK_IS_QR(_qr) && color !=NULL)
    {
        _qr->priv->draw_data.black= *color;
    }
}    ;

#endif





int gtk_qr_get_version(GtkQR *_qr)
{
    g_return_val_if_fail(GTK_IS_QR(_qr), GTKQR_NO_VERSION);
    return _qr->priv->data.qrversion_number;
}

int gtk_qr_get_mask(GtkQR *_qr)
{
    g_return_val_if_fail(GTK_IS_QR(_qr), GTKQR_NO_MASK);
    return _qr->priv->data.mask;
}


GtkQRData gtk_qr_get_mode(GtkQR *_qr)
{
    g_return_val_if_fail(GTK_IS_QR(_qr), GTKQR_DATA_NULL);
    return _qr->priv->data.data_coding;

}

GtkQRVersion gtk_qr_get_version_type(GtkQR *_qr)
{
    g_return_val_if_fail(GTK_IS_QR(_qr), GTKQR_VERSION_QR_NULL);
    return _qr->priv->data.qrversion;

}

void gtk_qr_set_micro(GtkQR *_qr,gboolean set)
{
    if(GTK_IS_QR(_qr))
    {
        _qr->priv->data.isMicro = set;
    }

}

void gtk_qr_set_save_text(GtkQR *_qr,gboolean set)
{
    if(GTK_IS_QR(_qr))
        _qr->priv->save_text = set;
}

void gtk_qr_set_UFT8(GtkQR *_qr,gboolean set)
{
    if(GTK_IS_QR(_qr))
    {
        _qr->priv->data.enable_UTF8 = set;
    }
}


static void draworder(GtkQR *_qr)
{
    if( ! _qr->priv->order_draw )
    {
        _qr->priv->order_draw= 1;
        gtk_widget_queue_draw(GTK_WIDGET(_qr));
    }

}

void gtk_qr_regenerate(GtkQR *_qr)
{

    if(GTK_IS_QR(_qr) && _qr->priv->text != NULL)
    {
        set_text(_qr->priv, (const char *)_qr->priv->text,FALSE);
        draworder(_qr);
    }
}

void   gtk_qr_set_dynamic_margin(GtkQR *_qr,gboolean set)
{
    if(GTK_IS_QR(_qr))
    {
        _qr->priv->dynamic_margin = set;


        if (set)
            _qr->priv->margin = (float)_qr->priv->data.num_modules / (_qr->priv->data.num_modules + 8 + _qr->priv->extra_margin);
        else
            _qr->priv->margin = 0.72413f;

    }
}

void   gtk_qr_set_extra_margin(GtkQR *_qr,int value)
{
    if(GTK_IS_QR(_qr))
    {
        _qr->priv->extra_margin = 2 * value;

        if(_qr->priv->extra_margin < 0)
            _qr->priv->extra_margin=0;
        else if ( _qr->priv->extra_margin > 10)
            _qr->priv->extra_margin =10;

        if (_qr->priv->dynamic_margin)
            _qr->priv->margin = (float)_qr->priv->data.num_modules / (_qr->priv->data.num_modules + 8 + _qr->priv->extra_margin);
        else
            _qr->priv->margin = 0.72413f;

    }
}

void gtk_qr_save_image(GtkQR *_qr,const char *file,int quality,int _size)
{
    char *_q=NULL;
    TypeImage type;
    Draw_Data draw_data;
    guint width;
    GdkPixbuf *pixbuf=NULL;
    cairo_surface_t * surface ;
    cairo_t * cr ;
#if GTK_CHECK_VERSION(3,0,0)
#else
    GdkPixbuf *pixbuf2=NULL;
    GdkRectangle rectangle;
    GdkPixmap *pixmap;
    GtkAllocation alloc;
    guint height;
#endif

    type= getTypeImage(file);

    if(type == TypeImageInvalid)
        return;




#if GTK_CHECK_VERSION(3,0,0)


    if(GTK_IS_QR(_qr))
    {
        surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24, _size,_size);
        cr = cairo_create (surface);

        draw_data.white= _qr->priv->draw_data.white;
        draw_data.black= _qr->priv->draw_data.black;

        gdk_cairo_set_source_rgba (cr, &draw_data.white);

        cairo_rectangle (cr, 0, 0, _size, _size);
        cairo_fill (cr);

        if (_qr->priv->draw_image)
        {
            width = _qr->priv->margin * _size;
            draw_data.size_modules = width / (double) _qr->priv->data.num_modules;
            draw_data.startX = (_size - width) /2 ;
            draw_data.startY =  draw_data.startX ;
            draw_data.width = width ;
            drawData(cr,&draw_data,_qr->priv->matrix);
        }


        pixbuf=gdk_pixbuf_get_from_surface(surface,0,0,_size,_size);


       if(quality>100)
                   quality=100;
       else if(quality < 0)
                   quality=0;



        _q = number_to_char(quality);

        switch(type)
        {
        case TipeJPG:
            gdk_pixbuf_save (pixbuf, file, "jpeg", NULL, "quality", (const char*) _q, NULL);
            break;
        case TipePNG:
            gdk_pixbuf_save (pixbuf, file, "png", NULL, "quality", (const char*) _q, NULL);
            break;
        case TypeBMP:
            gdk_pixbuf_save (pixbuf, file, "bmp", NULL, "quality", (const char*)_q, NULL);
            break;
        case TypeIco:
            gdk_pixbuf_save (pixbuf, file, "ico", NULL, "quality",(const char*) _q, NULL);
            break;

        default:

            break;
        }

        cairo_destroy (cr);
        cairo_surface_destroy (surface);
        g_object_unref (pixbuf);

    }

#else


    if(GTK_IS_QR(_qr))
    {
        gtk_widget_get_allocation(GTK_WIDGET(_qr), &alloc);

        width = alloc.width;
        height = alloc.height;

        if(width==0 || height ==0)
            return;

        if (type==TipePNG)
        {
            surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24, _size,_size);
            cr = cairo_create (surface);

            draw_data.white= _qr->priv->draw_data.white;
            draw_data.black= _qr->priv->draw_data.black;

            cairo_set_source_rgb(cr, _qr->priv->draw_data.white.red, _qr->priv->draw_data.white.green,_qr->priv->draw_data.white.blue);


            cairo_rectangle (cr, 0, 0, _size, _size);
            cairo_fill (cr);

            if (_qr->priv->draw_image)
            {
                width = _qr->priv->margin * _size;
                draw_data.size_modules = width / (double) _qr->priv->data.num_modules;
                draw_data.startX = (_size - width) /2 ;
                draw_data.startY =  draw_data.startX ;
                draw_data.width = width ;
                drawData(cr,&draw_data,_qr->priv->matrix);
            }

            cairo_surface_write_to_png (surface,file);
            cairo_destroy (cr);
            cairo_surface_destroy (surface);
            free(_q);


        }
        else
        {
            if(quality>100)
                   quality=100;
            else if(quality < 0)
                   quality=0;


            _q = number_to_char(quality);
            if(width > height)
            {
                rectangle.height = height;
                rectangle.width = height;
                rectangle.y = 0;
                rectangle.x = (width - height) /2 ;
            }
            else
            {
                rectangle.height = width;
                rectangle.width = width;
                rectangle.x = 0;
                rectangle.y = (height - width) /2 ;
            }

            pixmap = gtk_widget_get_snapshot (GTK_WIDGET(_qr),&rectangle);
            pixbuf=gdk_pixbuf_get_from_drawable(NULL, GDK_DRAWABLE (pixmap), NULL,0, 0, 0, 0, rectangle.width, rectangle.height);

            if(_size != rectangle.width)
                pixbuf2=gdk_pixbuf_scale_simple(pixbuf,_size,_size,GDK_INTERP_HYPER);
            else
                pixbuf2=gdk_pixbuf_copy(pixbuf);


            switch(type)
            {
            case TipeJPG:
                gdk_pixbuf_save (pixbuf2, file, "jpeg", NULL, "quality",(const char*) _q, NULL);
                break;
            case TypeBMP:
                gdk_pixbuf_save (pixbuf2, file, "bmp", NULL, "quality",(const char*) _q, NULL);
                break;
            case TypeIco:
                gdk_pixbuf_save (pixbuf2, file, "ico", NULL, "quality",(const char*) _q, NULL);
                break;

            default:

                break;
            }

            g_object_unref (pixbuf);
            g_object_unref (pixbuf2);
            gdk_drawable_unref(pixmap);
            free(_q);

     }

   }

#endif

}

char **   gtk_qr_get_qrmatrix(GtkQR *_qr)
{
    char **result=NULL;

    if(GTK_IS_QR(_qr) && _qr->priv->matrix != NULL)
    {
       result = (char **) malloc(  (_qr->priv->data.num_modules+1)* sizeof(char *));

       for(int i= 0; i < _qr->priv->data.num_modules ; i++ )
       {
            result[i] = (char *) malloc((_qr->priv->data.num_modules + 1)* sizeof(char));

            for(int a= 0; a < _qr->priv->data.num_modules ; a++ )
            {
                result[i][a] = _qr->priv->matrix[i][a];
            }
            result[i][_qr->priv->data.num_modules] = '\0';
       }

       result[_qr->priv->data.num_modules]=  NULL;
    }

    return result;
}

int   gtk_qr_get_number_character_encoding(GtkQR *_qr)
{
   g_return_val_if_fail(GTK_IS_QR(_qr), 0);

   return _qr->priv->data.num_eci_mode;
}

GtkQREciMode  gtk_qr_get_character_encoding(GtkQR *_qr,int position)
{
    g_return_val_if_fail(GTK_IS_QR(_qr), GTKQR_ECI_MODE_ISO_8859_1);

    if(position < _qr->priv->data.num_eci_mode )
    {
          return _qr->priv->data.eci_mode[position];

    }

    return GTKQR_ECI_MODE_ISO_8859_1;
}

