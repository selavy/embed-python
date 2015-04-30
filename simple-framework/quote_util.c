#include "quote_util.h"

static PyObject * LastTradeString;
static PyObject * BidString;
static PyObject * AskString;
static PyObject * LastTradeValue;
static PyObject * BidValue;
static PyObject * AskValue;

/*
 * TODO (plesslie);
 * even better would be to keep a reference to the already
 * made dict and just set the values each time and pass
 * back out a reference to the module's dict
 */

int QuoteUtil_Initialize() {
    LastTradeString = 0;
    BidString = 0;
    AskString = 0;
    LastTradeValue = 0;
    BidValue = 0;
    AskValue = 0;

    LastTradeString = PyString_FromString( "lt" );
    BidString = PyString_FromString( "bid" );
    AskString = PyString_FromString( "ask" );
    LastTradeValue = PyFloat_FromDouble( 0.0 );
    BidValue = PyFloat_FromDouble( 0.0 );
    AskValue = PyFloat_FromDouble( 0.0 );

    return ! ( LastTradeString && BidString && AskString && LastTradeValue && BidValue && AskValue );
}

int QuoteUtil_Finalize() {
    if ( LastTradeString ) {
        Py_XDECREF( LastTradeString );
        LastTradeString = 0;
    }
    if ( BidString ) {
        Py_XDECREF( BidString );
        BidString = 0;
    }
    if ( AskString ) {
        Py_XDECREF( AskString );
        AskString = 0;
    }
    if ( LastTradeValue ) {
        Py_XDECREF( LastTradeValue );
        LastTradeValue = 0;
    }
    if ( BidValue ) {
        Py_XDECREF( BidValue );
        BidValue = 0;
    }
    if ( AskValue ) {
        Py_XDECREF( AskValue );
        AskValue = 0;
    }

    return 0;
}

PyObject * QuoteUtil_QuoteToDict( struct Quote * quote ) {
    PyObject * quoteDict = PyDict_New();

    if ( !quoteDict ) {
        return 0;
    }

    BidValue = PyFloat_FromDouble( quote->bid / 10000.0 );
    if ( !BidValue ) {
        return 0;
    }
    AskValue = PyFloat_FromDouble( quote->ask / 10000.0 );
    if ( !AskValue) {
        return 0;
    }
    LastTradeValue = PyFloat_FromDouble( quote->lt / 10000.0 );
    if ( !LastTradeValue ) {
        return 0;
    }

    if ( PyDict_SetItem( quoteDict, LastTradeString, LastTradeValue ) != 0 ) {
        return 0;
    }
    if ( PyDict_SetItem( quoteDict, BidString, BidValue ) != 0 ) {
        return 0;
    }
    if ( PyDict_SetItem( quoteDict, AskString, AskValue ) != 0 ) { 
        return 0;
    }

    return quoteDict;
}
