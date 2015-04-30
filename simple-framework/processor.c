#include "processor.h"
#include <stdlib.h>
#include <stdio.h>
#include "python_module_loader.h"
#include "quote_source.h"
#include "quote_util.h"

#define MAX_STR_SZ 256


int Processor_Initialize( struct Processor* proc, char* prog, char* module, char* function ) {
    if ( !module || !function || !prog || !proc ) {
        return 1;
    }

    proc->qsrc = malloc( sizeof( *(proc->qsrc) ) );
    if ( !proc->qsrc ) {
        return 1;
    }

    proc->util = malloc( sizeof( *(proc->util) ) );
    if ( !proc->util ) {
        free( proc->qsrc );
        return 1;
    }

    proc->moduleNameSz = strnlen( module, MAX_STR_SZ );
    proc->functionNameSz = strnlen( function, MAX_STR_SZ );

    proc->moduleName = malloc( proc->moduleNameSz + 1 );
    proc->functionName = malloc( proc->functionNameSz + 1 );

    if ( !proc->moduleName || !proc->functionName ) {
        free( proc->moduleName );
        free( proc->functionName );
        return 2;
    }

    strncpy( proc->moduleName, module, proc->moduleNameSz );
    strncpy( proc->functionName, function, proc->functionNameSz );
    proc->moduleName[ proc->moduleNameSz + 1 ] = '\0';
    proc->functionName[ proc->functionNameSz + 1 ] = '\0';

    fprintf( stdout, "Loading Module Name '%s'", proc->moduleName );
    fprintf( stdout, "Loading Function Name '%s'", proc->functionName );

    fprintf( stdout, "Loading Python Module Loader..." );
    if ( PythonModuleLoader_Initialize( prog ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Python Module Loader!\n" );
        return 3;
    }

    fprintf( stdout, "Loading Quote Util Module..." );
    if ( QuoteUtil_Initialize( proc->util ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to load Quote Util Module!\n" );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Loading Quote Source..." );
    if ( QuoteSource_Initialize( proc->qsrc, proc->util ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to initialize Quote Source!\n" );
        PythonModuleLoader_Finalize();
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    printf( "Loading Module '%s'...", proc->moduleName ); 
    proc->module = PythonModuleLoader_LoadModule( proc->moduleName );
    if ( !proc->module ) {
        fprintf( stdout, "Failure!\nUnable to load module: '%s'\n", proc->moduleName );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( proc->qsrc );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Loading Function '%s' from Module '%s'...", proc->functionName, proc->moduleName );
    proc->function = PythonModuleLoader_LoadFunctionFromModule( proc->module, proc->functionName );
    if ( !proc->function ) {
        fprintf( stdout, "Failure!\nUnable to load function '%s' from module '%s'\n", proc->functionName, proc->moduleName );
        PythonModuleLoader_UnloadModule( proc->module );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( proc->qsrc );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Registering Python Quote Callback..." );
    if ( QuoteSource_SetQuoteCB( proc->qsrc, proc->function ) != 0 ) {
        fprintf( stdout, "Failure!\nUnable to register Python Quote Callback\n" );
        PythonModuleLoader_UnloadModule( proc->module );
        PythonModuleLoader_Finalize();
        QuoteSource_Finalize( proc->qsrc );
        exit( 1 );
    }
    fprintf( stdout, " Success.\n" );

    return 0;
}

int Processor_HandleQuote( struct Processor* proc, struct Quote* quote ) {
    if ( QuoteSource_HandleQuote( proc->qsrc, quote ) != 0 ) {
        fprintf( stdout, "Failure in QuoteSource_HandleQuote!\n" );
        if ( PyErr_Occurred() ) {
            PyErr_PrintEx( 0 );
            return 1;
        }
    }
    return 0;
}

int Processor_Finalize( struct Processor* proc ) {
    fprintf( stdout, "Destroying Quote Util..." );
    QuoteUtil_Finalize( proc->util );
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Destroying Quote Source..." );
    QuoteSource_Finalize( proc->qsrc );
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Unloading Python Function Object From Module..." );
    PythonModuleLoader_UnloadFunctionFromModule( proc->function );
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Unloading Python Module..." );
    PythonModuleLoader_UnloadModule( proc->module );
    fprintf( stdout, " Success.\n" );

    fprintf( stdout, "Destroying Python Module Loader..." );
    PythonModuleLoader_Finalize();
    fprintf( stdout, " Success.\n" );
    return 0;
}
