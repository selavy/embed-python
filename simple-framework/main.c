#include <stdio.h>
#include <stdlib.h>
#include "quote_source.h"

int main( int argc, char **argv ) {
    struct QuoteSource qsrc;
    QuoteSource_Initialize( &qsrc );

    struct Quote quote;
    Quote_Initialize( &quote );
    quote.bid = 1000000;
    quote.ask = 1000100;
    quote.lt =   990000;

    QuoteSource_HandleQuote( &qsrc, &quote );

    Quote_Finalize( &quote );

    QuoteSource_Finalize( &qsrc );
    return 0;
}
