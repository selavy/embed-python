#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#include <stdio.h>
#include <stdlib.h>
/*
#include "python_module_loader.h"
#include "quote_source.h"
#include "quote_util.h"
*/
#include "processor.h"

int main( int argc, char **argv ) {
    struct Quote quote;
    char * DefaultModule = "quote_callback";
    char * DefaultFunction = "quoteCb";
    char * moduleName;
    char * functionName;
    struct Processor processor;

    if ( argc < 2 ) {
        moduleName = DefaultModule;
        functionName = DefaultFunction;
    } else if ( argc == 3 ) {
        moduleName = argv[2];
        functionName = DefaultFunction;
    } else {
        moduleName = argv[2];
        functionName = argv[3];
    }

    fprintf( stdout, "Module: '%s'\n", moduleName );
    fprintf( stdout, "Function: '%s'\n", functionName );

    fprintf( stdout, "Loading Quote..." );
    if ( Quote_Initialize( &quote ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Quote object!\n" );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    Processor_Initialize( &processor, argv[0], moduleName, functionName );

    quote.bid = 1000000;
    quote.ask = 1000100;
    quote.lt =   990000;

    if ( Processor_HandleQuote( &processor, &quote ) != 0 ) {
        fprintf( stdout, "Failed to handle quote!!!\n" );
        if ( PyErr_Occurred() ) {
            PyErr_PrintEx( 0 );
        }
    }

    Processor_Finalize( &processor );
    return 0;
}
