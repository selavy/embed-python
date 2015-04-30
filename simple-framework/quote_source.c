#include "quote_source.h"
#include <stdio.h>
#include <stdlib.h>
#include "quote_util.h"

int QuoteSource_Initialize( struct QuoteSource* src, struct QuoteUtil* util ) {
    src->quoteCB = 0;
    src->util = util;
    return 0;
}

int QuoteSource_Finalize( struct QuoteSource* src ) {
    if ( src->quoteCB ) {
        Py_DECREF( src->quoteCB );
    }

    src->quoteCB = 0;
    return 0;
}

int QuoteSource_HandleQuote( struct QuoteSource* src, struct Quote* quote ) {
    char * txt = Quote_ToString( quote );
    int ret = 0;
    printf( "[QuoteSource_HandleQuote] received quote: %s\n", txt );
    free( txt );

    if ( src->quoteCB ) {
        //
        // TODO get the quote data and put in a python dict
        //

        PyObject* args = PyTuple_New( 1 );
        //
        // TODO convert quote to python dict
        //
        PyObject* pyQuote = QuoteUtil_QuoteToDict( src->util, quote );
        if ( !pyQuote ) {
            return 1;
        }
        PyTuple_SetItem( args, 0, pyQuote );
        if ( PyObject_CallObject( src->quoteCB, args ) == 0 ) {
            ret = 1;
        }

        Py_DECREF( args );
        Py_DECREF( pyQuote );
        //src->quoteCB( quote );
    }
    return ret;
}

int QuoteSource_SetQuoteCB( struct QuoteSource* src, PyObject* quoteCB ) {
    if ( !quoteCB || !PyCallable_Check( quoteCB ) ) {
        return 1;
    }

    if ( src->quoteCB ) {
        Py_DECREF( src->quoteCB );
    }

    src->quoteCB = quoteCB;
    return 0;
}

