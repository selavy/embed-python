#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <Python.h>

void
DoChildProc(char *prog, char *mod, char *func) {
    PyObject *value, *module, *function, *args;
    Py_SetProgramName( prog );
    Py_Initialize();
    value = PyString_FromString( mod );
    if ( !value ) {
        perror( "PyString_FromString" );
        goto finalize;
    }

    module = PyImport_Import( value );
    Py_DECREF( value );
    if ( !module ) {
        if ( PyErr_Occurred() ) {
            PyErr_Print();
        }
        goto finalize;
    }

    function = PyObject_GetAttrString( module, func );
    if ( function && PyCallable_Check( function ) ) {
        args = PyTuple_New( 0 );
        value = PyObject_CallObject( function, args );
    } else {
        printf( "Cannot find function \"%s\"\n", func );
    }
    Py_XDECREF( function );
    Py_DECREF( module );

finalize:
    Py_Finalize();
}

int
main( int argc, char *argv[] ) {
    pid_t pid, w;
    int status;

    printf( "parent::fork()\n" );
    pid = fork();
    if ( pid == -1 ) {
        perror( "fork" );
        exit( 0 );
    }
    else if ( pid == 0 ) {
        printf( "in child! pid = %d\n", getpid() );
        DoChildProc( argv[0], "simple", "callable" );
    }
    else {
        printf( "in parent! parent pid = %d, child pid = %d\n", getpid(), pid );
        do {
            w = waitpid( pid, &status, WUNTRACED | WCONTINUED );
            if ( w == -1 ) {
                perror( "waitpid" );
                exit( 1 );
            }
            else if ( WIFEXITED( status ) ) {
                printf( "exited, status=%d\n", WEXITSTATUS( status ) );
            }
            else if ( WIFSTOPPED( status ) ) {
                printf( "killed by signal, %d\n", WTERMSIG( status ) );
            }
            else if ( WIFCONTINUED( status ) ) {
                printf( "continue\n" );
            }
        } while ( !WIFEXITED( status ) && ! WIFSIGNALED( status ) );
    }
    return 0;
}
