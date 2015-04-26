#include <Python/Python.h>

int
main( int argc, char **argv )
{
    PyObject *pName, *pModule, *pDict, *pFunc, *sys, *path;
    PyObject *pArgs, *pValue;
    int i;

    if ( argc < 3 ) {
        fprintf( stderr, "Usage: %s pythonfile funcname [args]\n", argv[0] );
        return 1;
    }

    Py_SetProgramName( argv[0] );
    Py_Initialize();
    /*
     *sys = PyImport_ImportModule( "sys" );
     *if ( sys == NULL ) {
     *    fprintf( stderr, "Unable to load sys module" );
     *    PyErr_Print();
     *    return 1;
     *}
     *path = PyObject_GetAttrString( sys, "path" );
     *if ( path == NULL ) {
     *    fprintf( stderr, "Unable to load path from sys module" );
     *    PyErr_Print();
     *    return 1;
     *}
     *PyList_Append( path, PyUnicode_FromString( "." ) );
     */
    pName = PyString_FromString( argv[1] );
    /* Error checking of pName left out */

    pModule = PyImport_Import( pName );
    Py_DECREF( pName );

    if ( pModule != NULL ) {
        pFunc = PyObject_GetAttrString( pModule, argv[2] );
        /* pFunc is a new reference */

        if ( pFunc != NULL && PyCallable_Check( pFunc ) ) {
            pArgs = PyTuple_New( argc - 3 );
            for ( i = 0; i < argc - 3; ++i ) {
                pValue = PyInt_FromLong( atoi( argv[i + 3] ) );
                if ( pValue == NULL ) {
                    Py_DECREF( pArgs );
                    Py_DECREF( pModule );
                    fprintf( stderr, "Cannot convert arguments\n" );
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem( pArgs, i, pValue );
            }
            pValue = PyObject_CallObject( pFunc, pArgs );
            Py_DECREF( pArgs );
            if ( pValue != NULL ) {
                printf( "Result of call: %ld\n", PyInt_AsLong( pValue ) );
                Py_DECREF( pValue );
            }
            else {
                Py_DECREF( pFunc );
                Py_DECREF( pModule );
                PyErr_Print();
                fprintf( stderr, "Call failed\n" );
                return 1;
            }
        }
        else {
            if ( PyErr_Occurred() ) {
                PyErr_Print();
            }
            fprintf( stderr, "Cannot find function \"%s\"\n", argv[2] );
        }
        Py_XDECREF( pFunc );
        Py_DECREF( pModule );
    }
    else {
        PyErr_Print();
        fprintf( stderr, "Failed to load \"%s\"\n", argv[1] );
        return 1;
    }
    Py_Finalize();
    return 0;
}

