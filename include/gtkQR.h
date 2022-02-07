#ifndef GTKQR_H_INCLUDED
#define GTKQR_H_INCLUDED
#include <gtk/gtk.h>
#include "QrDefinitions.h"





G_BEGIN_DECLS

/* Standart GObject macros */
#define GTK_TYPE_QR (gtk_qr_get_type())
#define GTK_QR(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_QR, GtkQR))
#define GTK_QR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_QR, GtkQRClass))
#define GTK_IS_QR(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_QR))
#define GTK_IS_QR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_QR))
#define GTK_QR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_QR, GtkQRClass))

/* Type definition */
/// @private
typedef struct _GtkQR        GtkQR;
/// @private
typedef struct _GtkQRClass   GtkQRClass;

/// @private
typedef struct _GtkQRPrivate GtkQRPrivate;

/// @private
struct _GtkQR {

   GtkWidget parent;
   /*< Private >*/
   GtkQRPrivate *priv;
};

/// @private
struct _GtkQRClass {

   GtkWidgetClass parent_class;

};

/// @private
GType gtk_qr_get_type(void) G_GNUC_CONST;

/** \brief Creates a new empty widget GtkQR without any image
 *
 * \return empty GtkQR
 *
 */
GtkWidget *gtk_qr_new(void);


/** \brief Creates a new widget GtkQR with text
 *
 * \param  text : text you want to encode
 * \return GtkQR widget
 * \details The text is encoded according to the following order, choosing the first possible one:
 * #GTKQR_DATA_NUMERIC, #GTKQR_DATA_ALPHANUMERIC , #GTKQR_DATA_BYTE <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-1">ISO/IEC 8859-1</a>,
 * if the text to be encoded has characters that do not belong to this encoding set then proceed in ECI mode (UTF8 or other ISO/IEC 8859-X ).
 * finally try Kanji ,if encoding is not possible due to invalid characters or excessive length, no image is displayed.
 * .Default error correction level is #GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM
 * \note  Not all readers support ECI mode , UTF8 or ISO/IEC 8859-X
 */
GtkWidget *gtk_qr_new_with_text(const char *text);



/** \brief Creates a new widget GtkQR with text and error correction level
 *
 * \param text :text you want to encode
 * \param error_level_correction : #GtkQRErrorCorrectionLevel for qr image
 * \return GtkQR widget
 * \details The text is encoded according to the following order, choosing the first possible one:
 * #GTKQR_DATA_NUMERIC, #GTKQR_DATA_ALPHANUMERIC , #GTKQR_DATA_BYTE <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-1">ISO/IEC 8859-1</a>,
 * if the text to be encoded has characters that do not belong to this encoding set then proceed in ECI mode (UTF8 or other ISO/IEC 8859-X ).
 * finally try Kanji ,if encoding is not possible due to invalid characters or excessive length, no image is displayed.
 * \note  Not all readers support ECI mode , UTF8 or ISO/IEC 8859-X
 */
GtkWidget *gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction);


/** \brief  Get the error correction level of the QR image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return #GtkQRErrorCorrectionLevel
 *
 */
GtkQRErrorCorrectionLevel gtk_qr_get_correction(GtkQR *widget);

/** \brief Get text of the widget GtkQR
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return text of widget GtkQR ,
 * if you disable save text with function
 * \ref gtk_qr_set_save_text(GtkQR *widget,gboolean set_save_text) "gtk_qr_set_save_text"
 * text of widget is empty
 */
const char * gtk_qr_get_text(GtkQR *widget);

/** \brief set text of the widget and regenerates it
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param text: text you want to encode
 * \note GtkQR error correction level is the same as the previous.
 */
void gtk_qr_set_text(GtkQR *widget,const char *text);

/** \brief set text and error correction level of the widget and regenerates it
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param text :text you want to encode
 * \param error_level_correction : #GtkQRErrorCorrectionLevel for qr image
 */
void gtk_qr_set_text_and_correction(GtkQR *widget,const char *text,GtkQRErrorCorrectionLevel error_level_correction);

  #ifdef __DOXYGEN
    /** \brief change the background color in GTK3 & GTK4
     *
     * \param  widget : GtkQR create with
     * \ref gtk_qr_new(void) "gtk_qr_new" ,
     * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
     * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
     * \param color : <a href="https://docs.gtk.org/gdk3/struct.RGBA.html">GdkRGBA</a> color
     *
     */
    void gtk_qr_set_background_color(GtkQR *widget,GdkRGBA *color);

    /** \brief change the foreground color in GTK3 & GTK4
     *
     * \param  widget : GtkQR create with
     * \ref gtk_qr_new(void) "gtk_qr_new" ,
     * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
     * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
     * \param color : <a href="https://docs.gtk.org/gdk3/struct.RGBA.html">GdkRGBA</a> color
     *
     */
    void gtk_qr_set_foreground_color(GtkQR *widget,GdkRGBA *color);
  #endif

  #if GTK_CHECK_VERSION(3,0,0)
    void gtk_qr_set_background_color(GtkQR *widget,GdkRGBA *color);
    void gtk_qr_set_foreground_color(GtkQR *widget,GdkRGBA *color);
  #else

    /** \brief change the background color  in GTK2
     *
     * \param  widget : GtkQR create with
     * \ref gtk_qr_new(void) "gtk_qr_new" ,
     * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
     * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
     * \param color <a href="https://docs.gtk.org/gdk3/struct.Color.html">GdkColor</a> color
     *
     */
     void gtk_qr_set_background_color(GtkQR *widget,GdkColor *color);

     /** \brief change the foreground color in GTK2
      *
      * \param  widget : GtkQR create with
      * \ref gtk_qr_new(void) "gtk_qr_new" ,
      * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
      * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
      * \param color <a href="https://docs.gtk.org/gdk3/struct.Color.html">GdkColor</a> color
      *
      */
      void gtk_qr_set_foreground_color(GtkQR *widget,GdkColor *color);
  #endif


/** \brief Get version number of the widget GtkQR according to the encrypted text
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return version number
 * \details Version number are 1 to 40 for QR and #GTKQR_VERSION_NUMBER_M1 , #GTKQR_VERSION_NUMBER_M2 ,
 *  #GTKQR_VERSION_NUMBER_M3 and #GTKQR_VERSION_NUMBER_M4 for micro QR
 * .If QR can't render the image return #GTKQR_NO_VERSION
 */
int  gtk_qr_get_version(GtkQR *widget);

/** \brief Get mask pattern for qr image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return  number 0 to 7
 *
 */
int  gtk_qr_get_mask(GtkQR *widget);

/** \brief Get type of data for qr image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return #GtkQRData
 *
 */
GtkQRData      gtk_qr_get_mode(GtkQR *widget);

/** \brief Get version enum for qr image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \return #GtkQRVersion
 *
 */
GtkQRVersion   gtk_qr_get_version_type(GtkQR *widget);

/** \brief the micro QR ,default:FALSE
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param set_micro :TRUE to use Micro QR, FALSE to use QR
 *
 */
void   gtk_qr_set_micro(GtkQR *widget,gboolean set_micro);

/** \brief Save text in GtkQR ,default:TRUE
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param set_save_text :TRUE to save text, FALSE otherwise
 * \details Not saving the text in memory we save memory but it has the disadvantage that when using the
 * \ref gtk_qr_set_dynamic_margin(GtkQR *widget,gboolean set_dynamic) "gtk_qr_set_dinamic_margin" ,
 * \ref gtk_qr_set_extra_margin(GtkQR *widget,int size_margin) "gtk_qr_set_extra_margin" ,
 * \ref gtk_qr_set_micro(GtkQR *widget,gboolean set_micro) "gtk_qr_set_micro" or
 * \ref gtk_qr_set_UFT8(GtkQR *widget,gboolean set_UTF8) "gtk_qr_set_UFT8" or
 * change color functions you have to re-enter the text to regenerate the image
 *
 */
void   gtk_qr_set_save_text(GtkQR *widget,gboolean set_save_text);

/** \brief Allows the encoding of characters in UTF8 ,default:TRUE
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param set_UTF8 :TRUE to allow UTF8, FALSE otherwise
 * \details In <a href="https://en.wikipedia.org/wiki/Extended_Channel_Interpretation">Extended Channel Interpretation</a> allows the encoding of characters in <a href="https://en.wikipedia.org/wiki/UTF-8">UTF8</a>  when using characters not included in <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-1">ISO/IEC 8859-1</a>,
 * if you disable this option then it will use the following encoding :
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-2">ISO/IEC 8859-2</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-3">ISO/IEC 8859-3</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-4">ISO/IEC 8859-4</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-5">ISO/IEC 8859-5</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-6">ISO/IEC 8859-6</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-7">ISO/IEC 8859-7</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-8">ISO/IEC 8859-8</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-9">ISO/IEC 8859-9</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-10">ISO/IEC 8859-10</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-11">ISO/IEC 8859-11</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-13">ISO/IEC 8859-13</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-14">ISO/IEC 8859-14</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-15">ISO/IEC 8859-15</a>,
 * <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-16">ISO/IEC 8859-16</a> or
 * <a href="https://en.wikipedia.org/wiki/Shift_JIS"> JIS X 0201</a>
 * \n.With UTF8 you will have all the characters but occupying more space for the encoding, in case of using ISO/IEC 8859-2 to JIS X 0201 the encoding uses less space but not all the characters are possible
 */
void   gtk_qr_set_UFT8(GtkQR *widget,gboolean set_UTF8);

/** \brief regenerate qr image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \details Some functions like
 * \ref gtk_qr_set_dynamic_margin(GtkQR *widget,gboolean set_dynamic) "gtk_qr_set_dinamic_margin" ,
 * \ref gtk_qr_set_extra_margin(GtkQR *widget,int size_margin) "gtk_qr_set_extra_margin" ,
 * \ref gtk_qr_set_micro(GtkQR *widget,gboolean set_micro) "gtk_qr_set_micro" or
 * \ref gtk_qr_set_UFT8(GtkQR *widget,gboolean set_UTF8) "gtk_qr_set_UFT8",
 * don't regenerate the image they only change options , if you use the above functions before
 * \ref gtk_qr_set_text(GtkQR *widget,const char *text) "gtk_qr_set_text" or
 * \ref gtk_qr_set_text_and_correction(GtkQR *widget,const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_set_text_and_correction"
 * no need to regenerate the image
 */
void   gtk_qr_regenerate(GtkQR *widget);

/** \brief Save the qr image
 *
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param file : filename to save
 * \param quality : quality of image , 0 to 100
 * \param _size : size of image
 * \details The following formats are supported : “jpeg”, “png”, “ico” and “bmp” ,
 * the format is recognized by the filename.In GTK2 it is better to use the png format
 *
 */
void  gtk_qr_save_image(GtkQR *widget,const char *file,int quality,int _size);

/** \brief  sets whether the margin is always the same ,default:TRUE
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param set_dynamic: FALSE is is always the same , TRUE otherwise
 * \details The QR standard establishes that at least 4 image margin modules are necessary
 * ,but the number of modules varies from 21x21 in version 1 to 170x170 in version 40 .if the parameter is set to false the margin is calculated in the worst case 21x 21 ,
 * if it is set to true the margin will depend on the number of modules or qr version
 *
 */
void  gtk_qr_set_dynamic_margin(GtkQR *widget,gboolean set_dynamic);

/** \brief   extra space added to the margins ,default:0
 * \param  widget : GtkQR create with
 * \ref gtk_qr_new(void) "gtk_qr_new" ,
 * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
 * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
 * \param size_margin: extra margin to add
 *
 */
void  gtk_qr_set_extra_margin(GtkQR *widget,int size_margin);


/** \brief Get the character matrix representing the QR from widget
 *
  * \param  widget : GtkQR create with
  * \ref gtk_qr_new(void) "gtk_qr_new" ,
  * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
  * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
  * \return character matrix
  * \details A QR image is made up of a series of rectangles called modules,
  * each value of the matrix is a coordinate (X,Y) that represents the different modules, being value '1'
  * for foreground color and '0' for background color.Before finish or create another matrix you have to call the function:
  * \ref freeQrMatrix(char **qrmatrix) "freeQrMatrix" to free memory.
  * \see \ref GetQrMatrix(const char *text,QR_Data *data) "GetQrMatrix"
  * \note the (0,0) coordinate is at the top left .
  */
char **   gtk_qr_get_qrmatrix(GtkQR *widget);


  /** \brief Get number character encoding
  *
  * \param  widget : GtkQR create with
  * \ref gtk_qr_new(void) "gtk_qr_new" ,
  * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
  * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
  * \return number of character encoding
  * \details Obtains the character encoding number, if the encodings
  * that are default (NUMERIC,ALPHANUMERIC,ISO/IEC 8859-1 or KANJI) returns 0.
  * Returning a number >=1 indicates that the <a href="https://en.wikipedia.org/wiki/Extended_Channel_Interpretation">Extended Channel Interpretation</a> is used
  */
int   gtk_qr_get_number_character_encoding(GtkQR *widget);

  /** \brief Get character encoding used in the QR
  *
  * \param  widget : GtkQR create with
  * \ref gtk_qr_new(void) "gtk_qr_new" ,
  * \ref gtk_qr_new_with_text(const char *text) "gtk_qr_new_with_text" or
  * \ref gtk_qr_new_with_text_and_correction(const char *text,GtkQRErrorCorrectionLevel error_level_correction) "gtk_qr_new_with_text_and_correction"
  * \param position :position of character enconding ,starts with 0
  * \return character encoding
  * \details Get character encoding used in the QR starting position 0 to
  * \ref gtk_qr_get_number_character_encoding(GtkQR *widget) "gtk_qr_get_number_character_encoding" -1
  * , if number of character_encoding is 0 always return #GTKQR_ECI_MODE_ISO_8859_1
  *
  */
GtkQREciMode  gtk_qr_get_character_encoding(GtkQR *widget,int position);


G_END_DECLS

#endif // GTKQR_H_INCLUDED
