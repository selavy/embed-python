#ifndef QUOTE_SOURCE__H_
#define QUOTE_SOURCE__H_

#include "quote.h"
#include <Python/Python.h>

struct QuoteSource {
//    void (*quoteCB)( struct Quote* quote );
    PyObject* quoteCB;
};

int QuoteSource_Initialize( struct QuoteSource* src );
int QuoteSource_Finalize( struct QuoteSource* src );
int QuoteSource_HandleQuote( struct QuoteSource* src, struct Quote* quote );
int QuoteSource_SetQuoteCB( struct QuoteSource* src, PyObject* quoteCB );

#endif // QUOTE_SOURCE__H_
