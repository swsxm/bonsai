#include <Python.h>

#include "../dataframe.h"

#define GEN_REPR_CASE(NAME, C_TYPE, PY_TO_C, C_TO_PY) \
  case NAME: {                                        \
    C_TYPE* array = (C_TYPE*)self->data;              \
    for (Py_ssize_t i = 0; i < self->size; i++) {     \
      PyObject* val = C_TO_PY(array[i]);              \
      PyList_SetItem(temp_list, i, val);              \
    }                                                 \
    break;                                            \
  }

PyObject* DataFrame__repr__(DataFrameObject* self) {
  PyObject* temp_list = PyList_New(self->size);
  if (!temp_list) return NULL;

  switch (self->dtype) {
    ALL_NUMERIC_TYPES(GEN_REPR_CASE)

    case DTYPE_STRING: {
      char** array = (char**)self->data;
      for (Py_ssize_t i = 0; i < self->size; i++) {
        PyList_SetItem(temp_list, i, PyUnicode_FromString(array[i]));
      }
      break;
    }
  }

  PyObject* list_repr = PyObject_Repr(temp_list);
  Py_DECREF(temp_list);
  if (!list_repr) return NULL;
  PyObject* s = PyUnicode_FromFormat("DataFrame(%S)", list_repr);
  Py_DECREF(list_repr);
  return s;
}
