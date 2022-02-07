#ifndef QrDefinitions_H_INCLUDED
#define QrDefinitions_H_INCLUDED

  /** \brief No version number
 */
  #define GTKQR_NO_VERSION 41

  /** \brief version number M1
 */
  #define GTKQR_VERSION_NUMBER_M1 -4

  /** \brief version number M2
 */
  #define GTKQR_VERSION_NUMBER_M2 -3

  /** \brief version number M3
 */
  #define GTKQR_VERSION_NUMBER_M3 -2


 /** \brief version number M4
 */
  #define GTKQR_VERSION_NUMBER_M4 -1

 /** \brief No mask applied
 */
  #define GTKQR_NO_MASK -1

 /** \brief Selectable error correction
 */
  typedef enum {GTKQR_ERROR_CORRECTION_LEVEL_LOW, /**< allowing recovery 7% codewords  */
                GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM,/**< allowing recovery 15% codewords  */
                GTKQR_ERROR_CORRECTION_LEVEL_QUALITY,/**< allowing recovery 25% codewords  */
                GTKQR_ERROR_CORRECTION_LEVEL_HIGH,/**< allowing recovery 30% codewords ,\n not available in micro QR */
                GTKQR_ERROR_CORRECTION_LEVEL_NOTHING /**< error detection only \n in version M1 micro QR  */
                 } GtkQRErrorCorrectionLevel;

 /** \brief QR and micro QR versions
 */
  typedef enum {GTKQR_VERSION_M1,GTKQR_VERSION_M2,GTKQR_VERSION_M3,GTKQR_VERSION_M4,
  GTKQR_VERSION_QR_1,GTKQR_VERSION_QR_2,GTKQR_VERSION_QR_3,GTKQR_VERSION_QR_4,GTKQR_VERSION_QR_5,GTKQR_VERSION_QR_6,GTKQR_VERSION_QR_7
  ,GTKQR_VERSION_QR_8,GTKQR_VERSION_QR_9,GTKQR_VERSION_QR_10,GTKQR_VERSION_QR_11,GTKQR_VERSION_QR_12,GTKQR_VERSION_QR_13,GTKQR_VERSION_QR_14,GTKQR_VERSION_QR_15,GTKQR_VERSION_QR_16,GTKQR_VERSION_QR_17,GTKQR_VERSION_QR_18,GTKQR_VERSION_QR_19,
  GTKQR_VERSION_QR_20,GTKQR_VERSION_QR_21,GTKQR_VERSION_QR_22,GTKQR_VERSION_QR_23,GTKQR_VERSION_QR_24,GTKQR_VERSION_QR_25,GTKQR_VERSION_QR_26,GTKQR_VERSION_QR_27,GTKQR_VERSION_QR_28,GTKQR_VERSION_QR_29,GTKQR_VERSION_QR_30,
  GTKQR_VERSION_QR_31,GTKQR_VERSION_QR_32,GTKQR_VERSION_QR_33,GTKQR_VERSION_QR_34,GTKQR_VERSION_QR_35,GTKQR_VERSION_QR_36,GTKQR_VERSION_QR_37,GTKQR_VERSION_QR_38,GTKQR_VERSION_QR_39,GTKQR_VERSION_QR_40,GTKQR_VERSION_QR_NULL
  } GtkQRVersion;

 /** \brief Character set types in text
 */
  typedef enum {GTKQR_DATA_NUMERIC, /*!< The data only contains the digits 0 to 9  */
                GTKQR_DATA_ALPHANUMERIC, /*!< The data only contains digits 0 - 9; upper case letters A -Z; nine other characters: space, $ % * + - . / :  */
                GTKQR_DATA_BYTE, /*!< The data only contains ISO/IEC 8859-1 */
                GTKQR_DATA_KANJI, /*!< Kanji character set in accordance with JIS X 0208 Annex 1 Shift Coded Representation \n .in QR Code can have values 8140HEX -9FFCHEX and E040HEX -EBBFHE*/
                GTKQR_DATA_NULL /*!< No data */
                } GtkQRData;

  /** \brief Standard character encodings
 */
  typedef enum {GTKQR_ECI_MODE_ISO_8859_1,GTKQR_ECI_MODE_ISO_8859_2,GTKQR_ECI_MODE_ISO_8859_3,GTKQR_ECI_MODE_ISO_8859_4,
                 GTKQR_ECI_MODE_ISO_8859_5,GTKQR_ECI_MODE_ISO_8859_6,GTKQR_ECI_MODE_ISO_8859_7,GTKQR_ECI_MODE_ISO_8859_8,
                 GTKQR_ECI_MODE_ISO_8859_9,GTKQR_ECI_MODE_ISO_8859_10,GTKQR_ECI_MODE_ISO_8859_11,GTKQR_ECI_MODE_ISO_8859_13,
                 GTKQR_ECI_MODE_ISO_8859_14,GTKQR_ECI_MODE_ISO_8859_15,GTKQR_ECI_MODE_ISO_8859_16,Shift_JIS,UTF_8     } GtkQREciMode;


  /** \brief Information container of a QR & micro QR ,is used for the function
   * \n .Some parameters are selectable before the function call (choose parameter) and others are obtained after parsing the QR (read parameter)
   * \see  GetQrMatrix(const char *,QR_Data *) "GetQrMatrix".
   */
   typedef struct  {

     GtkQRVersion qrversion; /**< QR and micro QR version , read parameter  */
     short qrversion_number; /**< QR and micro QR version number, read parameter  */
     int num_modules; /**< QR and micro QR number of modules, read parameter  */
     short mask;  /**< QR and micro QR number of mask, read parameter  */
     short isMicro; /**< enable o disable micro QR, choose parameter : set 0 to deactivate Micro QR and set 1 to activate  */
     short enable_UTF8; /**< enable o disable UTF8, choose parameter : set 0 to deactivate UTF8 and set 1 to activate  */
     GtkQREciMode *eci_mode; /**< QR and micro QR eci mode, read parameter  */
     int num_eci_mode ; /**< number of character encoding formats that the image has, if it only contains characters belonging to Numerical/alphanumeric/ISO 8859 1/Kanji its value is 0  ,  read parameter  */

     GtkQRData data_coding ; /**< QR and micro QR eci mode, read parameter  */
     GtkQRErrorCorrectionLevel correction_level; /**< QR and micro QR error correction level , choose parameter  */

     const char *error; /**< message in case of error if it is not possible create qr , read parameter  */
     const char *warning; /**< warning message, for example if you use #GTKQR_ERROR_CORRECTION_LEVEL_HIGH in micro QR ,read parameter*/

 } QR_Data;


#endif // QrDefinitions_H_INCLUDED
