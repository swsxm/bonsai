#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <Python.h>

typedef struct {
  PyObject_HEAD PyObject* columns;
  Py_ssize_t num_rows;
  Py_ssize_t num_columns;
} DataFrameObject;

void DataFrame__dealloc__(DataFrameObject* self);
int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwds);

#endif
