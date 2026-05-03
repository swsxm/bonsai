#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <Python.h>

typedef struct Dispatcher {
  Py_ssize_t size;
  void (*set)(void*, PyObject*);
  PyObject* (*get)(PyObject*, Py_ssize_t);
  char* dtype_name;
} Dispatcher;

extern const Dispatcher DISP_INT;
extern const Dispatcher DISP_BOOL;
extern const Dispatcher DISP_STRING;
extern const Dispatcher DISP_CHAR;
extern const Dispatcher DISP_FLOAT;

#endif
