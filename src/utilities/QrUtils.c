#include "QrUtils.h"
#include "QrProcesses.h"
#include "QrMatrixUtils.h"

char ** GetQrMatrix(const char *text ,QR_Data *data )
{
   if(data->correction_level != GTKQR_ERROR_CORRECTION_LEVEL_LOW &&
       data->correction_level != GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM &&
         data->correction_level != GTKQR_ERROR_CORRECTION_LEVEL_QUALITY &&
           data->correction_level != GTKQR_ERROR_CORRECTION_LEVEL_HIGH &&
             data->correction_level != GTKQR_ERROR_CORRECTION_LEVEL_NOTHING )
                                 data->correction_level = GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM;

   if(data->isMicro !=0 && data->isMicro !=1)
                            data->isMicro=0;

   if(data->enable_UTF8 !=0 && data->enable_UTF8 !=1)
                            data->enable_UTF8=1;


   return calculateMatrix(text ,data );

}

void  freeQrMatrix(char **data)
{
   if ( data !=NULL )
                 freeMatrix(data);

}

void freeQrData(QR_Data *data)
{
    if ( data !=NULL && data->num_eci_mode > 0)
    {
        free(data->eci_mode);
        data->eci_mode = NULL;
    }

}
