#ifndef COLUMN_H
#define COLUMN_H
#include <Python.h>

// Will be called as: X(ENUM, C_TYPE, PY_TO_C, C_TO_PY)
// Handle strings separately as they require an array of pointers.
#define ALL_TYPES(X)                                              \
  X(DTYPE_FLOAT, double, PyFloat_AsDouble, PyFloat_FromDouble)    \
  X(DTYPE_INT, long long, PyLong_AsLongLong, PyLong_FromLongLong) \
  X(DTYPE_BOOL, char, PyObject_IsTrue, PyBool_FromLong)

typedef enum {
#define GENERATE_ENUM(NAME, T, P2C, C2P) NAME,
  ALL_TYPES(GENERATE_ENUM)
#undef GENERATE_ENUM
      DTYPE_STRING
} ColumnDType;

typedef struct {
  PyObject_HEAD void* data;
  Py_ssize_t size;
  ColumnDType dtype;
  PyObject* name;
} ColumnObject;

extern PyTypeObject ColumnType;

void Column__dealloc__(ColumnObject* self);
int Column__init__(ColumnObject* self, PyObject* args, PyObject* kwds);

#endif
