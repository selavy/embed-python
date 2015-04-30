#ifndef QUOTE_SOURCE__H_
#define QUOTE_SOURCE__H_


#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#include "quote.h"
/* #include "quote_util.h" */

struct QuoteSource {
    PyObject* quoteCB;
    struct QuoteUtil* util;
};

struct QuoteUtil;

int QuoteSource_Initialize( struct QuoteSource* src, struct QuoteUtil* util );
int QuoteSource_Finalize( struct QuoteSource* src );
int QuoteSource_HandleQuote( struct QuoteSource* src, struct Quote* quote );
int QuoteSource_SetQuoteCB( struct QuoteSource* src, PyObject* quoteCB );

#endif // QUOTE_SOURCE__H_
