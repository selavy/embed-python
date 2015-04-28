#include "quote.h"
#include <stdio.h>
#include <stdlib.h>

int Quote_Initialize( struct Quote* quote ) {
    if ( !quote ) {
        return 1;
    }

    quote->lt = 0;
    quote->bid = 0;
    quote->ask = 0;
    return 0;
}

int Quote_Finalize( struct Quote* quote ) {
    return 0;
}

char * Quote_ToString( struct Quote* quote ) {
    char * buf = malloc( 256 );
    sprintf( buf, "quote: lt = %d, bid = %d, ask = %d", quote->lt, quote->bid, quote->ask );
    return buf;
}

