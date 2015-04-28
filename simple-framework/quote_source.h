#ifndef QUOTE_SOURCE__H_
#define QUOTE_SOURCE__H_

#include "quote.h"

struct QuoteSource {
    void (*quoteCB)( struct Quote* quote );
};

int QuoteSource_Initialize( struct QuoteSource* src );
int QuoteSource_Finalize( struct QuoteSource* src );
int QuoteSource_HandleQuote( struct QuoteSource* src, struct Quote* quote );

#endif // QUOTE_SOURCE__H_
