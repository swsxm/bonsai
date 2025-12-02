#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <Python.h>

typedef struct {
  PyObject_HEAD PyObject* columns;
  Py_ssize_t num_columns;
} DataFrameObject;

extern PyMemberDef DataFrame_members[];

void DataFrame__dealloc__(DataFrameObject* self);
int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwds);
PyObject* DataFrame__repr__(DataFrameObject* self);

#endif
