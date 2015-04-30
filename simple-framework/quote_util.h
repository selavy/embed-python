#ifndef QUOTE_UTIL__H_
#define QUOTE_UTIL__H_

#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#include "quote.h"

struct QuoteUtil {
    PyObject * LastTradeString;
    PyObject * BidString;
    PyObject * AskString;
    PyObject * LastTradeValue;
    PyObject * BidValue;
    PyObject * AskValue;
};

int QuoteUtil_Initialize( struct QuoteUtil * util );
int QuoteUtil_Finalize( struct QuoteUtil * util );
PyObject * QuoteUtil_QuoteToDict( struct QuoteUtil * util, struct Quote * quote );

#endif // QUOTE_UTIL__H_
