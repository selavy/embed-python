The embedded python interpreter does not add the current working directory to that path.

There are 2 solutions to this:

    1) set PYTHONPATH to .
        like: "export PYTHONPATH=."

    2) after calling Py_Initialize()
    PyObject *sys = PyImport_ImportModule( "sys" );
    PyObject *path = PyObject_GetAttrString( sys, "path" );
    PyList_Append( path, PyUnicode_FromString( "." ) );
