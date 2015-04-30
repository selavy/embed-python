#ifndef QUOTE_UTIL__H_
#define QUOTE_UTIL__H_

#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#include "quote.h"

int QuoteUtil_Initialize( void );
int QuoteUtil_Finalize( void );
PyObject * QuoteUtil_QuoteToDict( struct Quote * quote );

#endif // QUOTE_UTIL__H_
