#ifndef PYTHON_MODULE_LOADER__H_
#define PYTHON_MODULE_LOADER__H_

#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif

/*
 * TODO (plesslie);
 * for safer typing, create structs around PyObject* with a module
 * and a struct around PyObject* with callable.
 */

/*
 * typedef void* Module;
 * typedef void* Callable;
 */

int PythonModuleLoader_Initialize( char * progName );
PyObject * PythonModuleLoader_LoadModule( char * moduleName );
int PythonModuleLoader_UnloadModule( PyObject * module );
PyObject * PythonModuleLoader_LoadFunctionFromModule( PyObject * module, char * functionName );
int PythonModuleLoader_UnloadFunctionFromModule( PyObject * object );
int PythonModuleLoader_Finalize( void );

#endif
