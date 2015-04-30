#include "quote_util.h"
#include <stdio.h>

/*
 * TODO (plesslie);
 * even better would be to keep a reference to the already
 * made dict and just set the values each time and pass
 * back out a reference to the module's dict
 */

int QuoteUtil_Initialize( struct QuoteUtil* util ) {
    memset( util, 0, sizeof( *util ) );

    util->LastTradeString = PyString_FromString( "lt" );
    util->BidString = PyString_FromString( "bid" );
    util->AskString = PyString_FromString( "ask" );
    util->LastTradeValue = PyFloat_FromDouble( 0.0 );
    util->BidValue = PyFloat_FromDouble( 0.0 );
    util->AskValue = PyFloat_FromDouble( 0.0 );

    if ( ! ( util->LastTradeString && util->BidString && util->AskString && util->LastTradeValue && util->BidValue && util->AskValue ) ) {
        printf( "some python module failed\n" );
        Py_XDECREF( util->LastTradeString );
        Py_XDECREF( util->BidString );
        Py_XDECREF( util->AskString );
        Py_XDECREF( util->LastTradeValue );
        Py_XDECREF( util->BidValue );
        Py_XDECREF( util->AskValue );
        return 1;
    }

    return 0;
}

int QuoteUtil_Finalize( struct QuoteUtil* impl ) {
    if ( !impl ) {
        return 0;
    }

    if ( impl->LastTradeString ) {
        Py_XDECREF( impl->LastTradeString );
        impl->LastTradeString = 0;
    }
    if ( impl->BidString ) {
        Py_XDECREF( impl->BidString );
        impl->BidString = 0;
    }
    if ( impl->AskString ) {
        Py_XDECREF( impl->AskString );
        impl->AskString = 0;
    }
    if ( impl->LastTradeValue ) {
        Py_XDECREF( impl->LastTradeValue );
        impl->LastTradeValue = 0;
    }
    if ( impl->BidValue ) {
        Py_XDECREF( impl->BidValue );
        impl->BidValue = 0;
    }
    if ( impl->AskValue ) {
        Py_XDECREF( impl->AskValue );
        impl->AskValue = 0;
    }

    return 0;
}

PyObject* QuoteUtil_QuoteToDict( struct QuoteUtil* impl, struct Quote* quote ) {
    PyObject* quoteDict;
   
    if ( !impl ) {
        return 0;
    }

    quoteDict = PyDict_New();
    if ( !quoteDict ) {
        return 0;
    }

    Py_XDECREF( impl->BidValue );
    impl->BidValue = PyFloat_FromDouble( quote->bid / 10000.0 );
    if ( !impl->BidValue ) {
        return 0;
    }
    Py_XDECREF( impl->AskValue );
    impl->AskValue = PyFloat_FromDouble( quote->ask / 10000.0 );
    if ( !impl->AskValue) {
        return 0;
    }
    Py_XDECREF( impl->LastTradeValue );
    impl->LastTradeValue = PyFloat_FromDouble( quote->lt / 10000.0 );
    if ( !impl->LastTradeValue ) {
        return 0;
    }

    if ( PyDict_SetItem( quoteDict, impl->LastTradeString, impl->LastTradeValue ) != 0 ) {
        return 0;
    }
    if ( PyDict_SetItem( quoteDict, impl->BidString, impl->BidValue ) != 0 ) {
        return 0;
    }
    if ( PyDict_SetItem( quoteDict, impl->AskString, impl->AskValue ) != 0 ) { 
        return 0;
    }

    return quoteDict;
}
