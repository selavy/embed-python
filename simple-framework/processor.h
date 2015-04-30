#ifndef PROCESSOR__H_
#define PROCESSOR__H_

#include <Python.h>
#include "quote.h"

struct Processor {
    struct QuoteSource* qsrc;
    char* moduleName;
    int moduleNameSz;
    char* functionName;
    int functionNameSz;
    PyObject* module;
    PyObject* function;
    struct QuoteUtil* util;
};

int Processor_Initialize( struct Processor* processor, char* prog, char* module, char* function );
int Processor_HandleQuote( struct Processor* processor, struct Quote* quote );
int Processor_Finalize( struct Processor* processor );

#endif // PROCESSOR__H_
