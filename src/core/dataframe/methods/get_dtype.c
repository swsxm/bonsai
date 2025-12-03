#include <Python.h>

#include "../../core.h"

PyObject* DataFrameGetDtype(DataFrameObject* self, PyObject* args,
                            PyObject* kwds) {
  int col_index;

  if (!PyArg_ParseTuple(args, "i", &col_index)) return NULL;

  if (col_index < 0 || col_index >= self->num_columns) {
    PyErr_SetString(PyExc_IndexError, "Column index out of bounds");
    return NULL;
  }

  ColumnObject* col = (ColumnObject*)PyList_GetItem(self->columns, col_index);

  switch (col->dtype) {
#define GENERATE_DTYPE_CASE(ENUM, TYPE, P2C, C2P, FMT) \
  case ENUM:                                           \
    return PyUnicode_FromString(#ENUM);

    ALL_TYPES(GENERATE_DTYPE_CASE)
#undef GENERATE_DTYPE_CASE

    case DTYPE_STRING:
      return PyUnicode_FromString("DTYPE_STRING");

    default:
      return PyUnicode_FromString("UNKNOWN");
  }
}
