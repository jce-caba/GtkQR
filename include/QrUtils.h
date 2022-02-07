#ifndef QRUTILS_H_INCLUDED
#define QRUTILS_H_INCLUDED
#include "QrDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** \brief Get the character matrix representing the QR without need gtkqr widget
  *
  * \param text :text you want to encode
  * \param data :Container with input and output information
  * \return character matrix
  * \details A QR image is made up of a series of rectangles called modules,
  * each value of the matrix is a coordinate (X,Y) that represents the different modules, being value '1'
  * for foreground color and '0' for background color.Before finish or create another matrix you have to call the functions:
  * \ref freeQrData(QR_Data *data) "freeQrData" and
  * \ref freeQrMatrix(char **qrmatrix) "freeQrMatrix" to free memory.
  * Usage example  :  \include example1.cpp
  * \see \ref gtk_qr_get_qrmatrix(GtkQR *widget) "gtk_qr_get_qrmatrix"
  * \note the (0,0) coordinate is at the top left .
  */
 char ** GetQrMatrix(const char *text,QR_Data *data);

 /** \brief free QR matrix memory
  *
  * \param qrmatrix :character matrix obtained through the function
  * \ref GetQrMatrix(const char *text,QR_Data *data) "GetQrMatrix"
  */
  void    freeQrMatrix(char **qrmatrix);

 /** \brief free container memory
  *
  * \param data :Container after the function call
  * \ref GetQrMatrix(const char *text,QR_Data *data) "GetQrMatrix"
  *
  */
  void    freeQrData(QR_Data *data);

#ifdef __cplusplus
}
#endif

#endif // QRUTILS_H_INCLUDED
