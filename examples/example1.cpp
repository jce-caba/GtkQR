/***************************************************************************
 *                                                                         *
 *   This is an example of how to use the method without using the widget  *                                                   *
 *                                                                         *
 *   I used podofo pdf c++ library  (http://podofo.sourceforge.net/)       *
 *   but you can use another tool .                                        *
 *   It is important only to understand the method   DrawText              *
 ***************************************************************************/

#include <iostream>
#include <podofo/podofo.h>
#include "QrUtils.h"

using namespace PoDoFo;
void DrawText(const char *,PdfPainter *,PdfPage* );


void PrintHelp()
{
    std::cout << "This is a example application for the PoDoFo PDF library AND QR ." << std::endl
              << "It creates a small PDF file containing the text >Hello World!< and this QR" << std::endl
              << "Please see http://podofo.sf.net for more information" << std::endl << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  examplehelloworld [outputfile.pdf] [text]" << std::endl << std::endl;
}

void HelloWorld( const char* pszFilename ,const char* text)
{

    PdfStreamedDocument document( pszFilename );
    PdfPainter painter;
    PdfPage* pPage;
    PdfFont* pFont;

	try {
		pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
		if( !pPage )
		{
			PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
		}
		painter.SetPage( pPage );
		pFont = document.CreateFont( "Arial" );
		if( !pFont )
		{
			PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
		}

		pFont->SetFontSize( 18.0 );
		painter.SetFont( pFont );
		DrawText(text ,&painter,pPage);
    	painter.FinishPage();

		document.GetInfo()->SetCreator ( PdfString("examplahelloworld - A PoDoFo test application") );
		document.GetInfo()->SetAuthor  ( PdfString("Dominik Seichter") );
		document.GetInfo()->SetTitle   ( PdfString("Hello World") );
		document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
		document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );

		document.Close();
	} catch ( PdfError & e ) {

		try {
			painter.FinishPage();
		} catch( ... ) {

		}

		throw e;
	}
}

int main( int argc, char* argv[] )
{

    if( argc != 3 )
    {
        PrintHelp();
        return -1;
    }

    try {

         HelloWorld( argv[1] ,argv[2]);
    } catch( PdfError & eCode ) {

        eCode.PrintErrorMsg();
        return eCode.GetError();
    }


    try {

        PdfEncodingFactory::FreeGlobalEncodingInstances();
    } catch( PdfError & eCode ) {

        eCode.PrintErrorMsg();
        return eCode.GetError();
    }


    return 0;
}

void DrawText(const char *text,PdfPainter *painter,PdfPage* pPage)
{

     char ** QR_Matrix;
     QR_Data data;


     // QR_Data is an information container,
     // these 3 parameters (correction_level,isMicro and enable_UTF8) are to choose,
     // other parameters are obtained when creating the QR with GetQrMatrix

     data.correction_level=GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM;
     data.isMicro=0;
     data.enable_UTF8=1;

     //some variables
     int widthQR;
     int startX,startY;

     double with_modules;


     // Get QR Matrix
     QR_Matrix = GetQrMatrix(text ,&data );

     //Now data has QR information

    if(data.qrversion ==GTKQR_VERSION_QR_NULL)
        painter->DrawText( 60, pPage->GetPageSize().GetHeight() - 60, "Unable to create qr image");
    else
    {
        // Choose random width and start point Y , start point X is centered **/

        widthQR= 0.2f * pPage->GetPageSize().GetWidth();
        startX=(pPage->GetPageSize().GetWidth()-widthQR)/2;
        startY= pPage->GetPageSize().GetHeight() - 200;

        // QR is format by small rectangles called modules
        // calculate module size (width of QR / number of rows or columns ) :

        with_modules = (double) widthQR / data.num_modules;

        // draw text
        painter->DrawText( 60, pPage->GetPageSize().GetHeight() - 60, text );

        // iterate QR matrix points and draw when values is '1'
        // qr matrix start upper left but pdf start down left


        for(int i= 0; i < data.num_modules ; i++ )
        {
            for(int a= 0; a < data.num_modules ; a++ )
            {
                if(QR_Matrix[i][a] == '1')
                {
                  painter->Rectangle( startX + i*with_modules,startY - a*with_modules, with_modules,with_modules );

                }
            }
        }

        painter->FillAndStroke () ;

        //free memory before finish or create another matrix
        freeQrMatrix(QR_Matrix);
        freeQrData(&data);
    }


}

