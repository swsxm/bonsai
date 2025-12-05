#include <Python.h>

#include "../../core.h"

#define GENERATE_GET_CASE(ENUM, TYPE, PY_TO_C, C_TO_PY, FMT) \
  case ENUM: {                                               \
    TYPE val = ((TYPE*)self->data)[row_num];                 \
    return C_TO_PY(val);                                     \
  }

PyObject* ColumnGetItem(ColumnObject* self, int row_num) {
  if (row_num < 0 || row_num >= self->size) {
    PyErr_SetString(PyExc_IndexError, "Row index out of bounds.");
    return NULL;
  }

  switch (self->dtype) {
    ALL_TYPES(GENERATE_GET_CASE)
    case DTYPE_STRING:
      char** val = (char**)self->data;
      return PyUnicode_FromString(val[row_num]);
    default:
      PyErr_SetString(PyExc_TypeError, "Unknown column dtype.");
      return NULL;
  }
}
