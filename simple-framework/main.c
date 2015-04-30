#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "python_module_loader.h"
#include "quote_source.h"

int main( int argc, char **argv ) {
    struct QuoteSource qsrc;
    struct Quote quote;
    char * DefaultModule = "quote_callback";
    char * DefaultFunction = "quoteCb";
    char * moduleName;
    char * functionName;
    PyObject * module;
    PyObject * function;

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

    fprintf( stdout, "Loading Python Module Loader..." );
    if ( PythonModuleLoader_Initialize( argv[0] ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Python Module Loader!\n" );
        exit( 1 );
    }    
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Loading Quote Source..." );
    if ( QuoteSource_Initialize( &qsrc ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Quote Source!\n" );
        PythonModuleLoader_Finalize();
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Loading Quote..." );
    if ( Quote_Initialize( &quote ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Quote object!\n" );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( &qsrc );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    printf( "Loading Module '%s'...", moduleName ); 
    module = PythonModuleLoader_LoadModule( moduleName );
    if ( !module ) {
        fprintf( stdout, "Failure!\nUnable to load module: '%s'\n", moduleName );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( &qsrc );
        Quote_Initialize( &quote );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Loading Function '%s' from Module '%s'...", functionName, moduleName );
    function = PythonModuleLoader_LoadFunctionFromModule( module, functionName );
    if ( !function ) {
        fprintf( stdout, "Failure!\nUnable to load function '%s' from module '%s'\n", functionName, moduleName );
        PythonModuleLoader_UnloadModule( module );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( &qsrc );
        Quote_Initialize( &quote );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    quote.bid = 1000000;
    quote.ask = 1000100;
    quote.lt =   990000;

    QuoteSource_HandleQuote( &qsrc, &quote );

    Quote_Finalize( &quote );

    QuoteSource_Finalize( &qsrc );

    PythonModuleLoader_UnloadModule( module );

    PythonModuleLoader_Finalize();

    return 0;
}
