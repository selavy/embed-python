#include "python_module_loader.h"

static int PythonModule_ProgramNameSet = 0;
static int PythonModule_InterpreterInitialized = 0;

int PythonModuleLoader_Initialize( char * progName  ) {
    if ( !PythonModule_ProgramNameSet ) {
        Py_SetProgramName( progName );
        PythonModule_ProgramNameSet = 1;
    }

    if ( !PythonModule_InterpreterInitialized ) {
        Py_Initialize();
        PythonModule_InterpreterInitialized = 1;
    }

    return 0;
}

PyObject * PythonModuleLoader_LoadModule( char * moduleName ) {
    PyObject * name;
    PyObject * module;

    name = PyString_FromString( moduleName );
    if ( !name ) {
        return 0;
    }

    module = PyImport_Import( name );
    Py_DECREF( name );

    if ( !module ) {
        return 0;
    }

    if ( !PyModule_Check( module ) ) {
        Py_DECREF( module );
        return 0;
    }

    return module;
}

int PythonModuleLoader_UnloadModule( PyObject * module ) {
    if ( !module ) {
        return 0;
    }

    Py_DECREF( module );
    return 0;
}

PyObject * PythonModuleLoader_LoadFunctionFromModule( PyObject * module, char * functionName ) {
    PyObject * callable;

    if ( !module ) {
        return 0;
    }

    callable = PyObject_GetAttrString( module, functionName );

    if ( !PyCallable_Check( callable ) ) {
        return 0;
    }

    return callable;
}

int PythonModuleLoader_UnloadFunctionFromModule( PyObject * object ) {
    if ( !object ) {
        return 0;
    }

    /*
     * XDECREF() will ignore NULL references
     */
    Py_XDECREF( object );
    return 0;
}

int PythonModuleLoader_Finalize( void ) {
    if ( PythonModule_InterpreterInitialized ) {
        Py_Finalize();
        PythonModule_InterpreterInitialized = 0;
    }

    return 0;
}
