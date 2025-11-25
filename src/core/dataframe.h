#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <Python.h>

typedef struct {
  PyObject_HEAD;
  double* data;
  Py_ssize_t size;
} DataFrameObject;

extern PyTypeObject DataFrameType;

#endif
