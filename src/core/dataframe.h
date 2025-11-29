#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <Python.h>
#include <stdbool.h>

// Will be called as: X(ENUM, C_TYPE, PY_TO_C, C_TO_PY)
#define ALL_TYPES(X)                                              \
  X(DTYPE_FLOAT, double, PyFloat_AsDouble, PyFloat_FromDouble)    \
  X(DTYPE_INT, long long, PyLong_AsLongLong, PyLong_FromLongLong) \
  X(DTYPE_BOOL, char, PyObject_IsTrue, PyBool_FromLong)           \
  // Handle strings separately as they require an array of pointers.

typedef enum {
#define GENERATE_ENUM(NAME, T, P2C, C2P) NAME,
  ALL_TYPES(GENERATE_ENUM)
#undef GENERATE_ENUM

      DTYPE_STRING
} DataFrameDType;

typedef struct {
  PyObject_HEAD void* data;
  Py_ssize_t size;
  DataFrameDType dtype;
} DataFrameObject;

extern PyTypeObject DataFrameType;

void DataFrame__dealloc__(DataFrameObject* self);
int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwds);
PyObject* DataFrame__repr__(DataFrameObject* self);

#endif
