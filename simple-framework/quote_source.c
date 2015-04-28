#include "quote_source.h"
#include <stdio.h>
#include <stdlib.h>

int QuoteSource_Initialize( struct QuoteSource* src ) {
    src->quoteCB = 0;
    return 0;
}

int QuoteSource_Finalize( struct QuoteSource* src ) {
    src->quoteCB = 0;
    return 0;
}

int QuoteSource_HandleQuote( struct QuoteSource* src, struct Quote* quote ) {
    char * txt = Quote_ToString( quote );
    printf( "[QuoteSource_HandleQuote] received quote: %s\n", txt );
    free( txt );

    if ( src->quoteCB ) {
        src->quoteCB( quote );
    }
    return 0;
}

