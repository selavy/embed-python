#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <Python.h>

struct ThreadArguments {
    int tid;
    char *prog;
    char *module;
};

#define FUNCTION "callback"

void *routine( void *arg ) {
    struct ThreadArguments *args = (struct ThreadArguments*) arg;
    PyObject *function, *module, *argument, *name, *value;
    printf( "Begin thread[%d] to load module(%s)\n", args->tid, args->module );
    Py_SetProgramName( args->prog );
    Py_Initialize();
    name = PyString_FromString( args->module );
    if ( !name ) { perror( "PyString_FromString" ); pthread_exit( 0 ); }
    module = PyImport_Import( name );
    if ( !module ) { PyErr_Print(); perror( "PyImport_Import" ); pthread_exit( 0 ); }
    Py_DECREF( name );
    function = PyObject_GetAttrString( module, FUNCTION );
    if ( !function || !PyCallable_Check( function ) ) {
        if ( PyErr_Occurred() ) {
            PyErr_Print();
        }
        fprintf( stderr, "'%s' is not a callable object in '%s'\n", FUNCTION, args->module );
        pthread_exit( 0 );
    }
    argument = PyTuple_New( 1 );
    value = PyInt_FromLong( args->tid );
    if ( !value ) { perror( "PyInt_FromLong" ); pthread_exit( 0 ); }
    PyTuple_SetItem( argument, 0, value );
    value = PyObject_CallObject( function, argument );
    Py_DECREF( argument );
    Py_Finalize();
    pthread_exit( 0 );
}

int main( int argc, char *argv[] ) {
    pthread_t *threads;
    pthread_attr_t *attrs;
    int nthreads;
    int i;
    struct ThreadArguments *args;
    void *res;

    if ( argc < 2 ) {
        printf( "Usage: %s [MODULE NAME]...\n", argv[0] );
        exit( 0 );
    }

    nthreads = argc - 1;
    threads = malloc( nthreads * sizeof( *threads ) );
    if ( !threads ) {
        perror( "malloc" );
        exit( 0 );
    }
    attrs = malloc( nthreads * sizeof( *attrs ) );
    if ( !attrs ) {
        perror( "malloc" );
        exit( 0 );
    }
    args = malloc( nthreads * sizeof( *args ) );
    if ( !args ) {
        perror( "malloc" );
        exit( 0 );
    }

    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_attr_init( &(attrs[i]) ) ) {
            perror( "pthread_attr_init" );
            exit( 0 );
        }
        args[i].tid = i;
        args[i].prog = argv[0];
        args[i].module = argv[i+1];
        printf( "creating arguments for thread: %d, module: '%s'\n", i, argv[i+1] );
    }

    /* begin creating threads */
    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_create( &(threads[i]), &(attrs[i]), routine, (void*) &(args[i]) ) ) {
            perror( "pthread_create" );
            exit( 0 );
        }
    }

    /* no longer need attrs so clean up */
    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_attr_destroy( &(attrs[i]) ) ) {
            perror( "pthread_attr_destroy" );
            exit( 0 );
        }
    }
    free( attrs );

    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_join( threads[i], &res ) ) {
            perror( "pthread_join" );
            exit( 0 );
        }
    }

    /* clean up threads and args */
    free( threads );
    free( args );

    return 0;
}
