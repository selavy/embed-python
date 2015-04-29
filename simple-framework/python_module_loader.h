#ifndef PYTHON_MODULE_LOADER__H_
#define PYTHON_MODULE_LOADER__H_

#ifdef OS_X
#include <Python/Python.h>
#else
#include <Python.h>
#endif

struct PythonModuleLoader {};

int PythonModuleLoader_Initialize( struct PythonModuleLoader* loader );
PyObject* PythonModuleLoader_LoadModule( struct PythonModuleLoader* loader, char * moduleName );
int PythonModuleLoader_Finalize( struct PythonModuleLoader* loader );

#endif
