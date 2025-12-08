#include <Python.h>
#include <string.h>

#include "../../core.h"

#define GEN_INIT_CASE(NAME, C_TYPE, PY_TO_C, C_TO_PY, FMT)              \
  case NAME: {                                                          \
    C_TYPE* array = (C_TYPE*)PyMem_Malloc(self->size * sizeof(C_TYPE)); \
    if (!array) return -1;                                              \
    for (Py_ssize_t i = 0; i < self->size; i++) {                       \
      PyObject* item = PyList_GetItem(input_list, i);                   \
      C_TYPE val = PY_TO_C(item);                                       \
      if (PyErr_Occurred()) {                                           \
        PyMem_Free(array);                                              \
        return -1;                                                      \
      }                                                                 \
      array[i] = val;                                                   \
    }                                                                   \
    self->data = array;                                                 \
    break;                                                              \
  }

int Column__init__(ColumnObject* self, PyObject* args, PyObject* kwgs) {
  PyObject* input_list;
  PyObject* name;
  if (!PyArg_ParseTuple(args, "OO!", &name, &PyList_Type, &input_list)) {
    return -1;
  }
  self->name = name;
  self->size = PyList_Size(input_list);
  if (self->size == 0) {
    self->data = NULL;
    return 0;
  }
  PyObject* first = PyList_GetItem(input_list, 0);
  if (PyFloat_Check(first)) self->dtype = DTYPE_FLOAT;
  // Order: Bool Check before INT
  else if (PyBool_Check(first))
    self->dtype = DTYPE_BOOL;
  else if (PyLong_Check(first))
    self->dtype = DTYPE_INT;
  else if (PyUnicode_Check(first))
    self->dtype = DTYPE_STRING;
  else {
    PyErr_SetString(PyExc_TypeError, "Unsupported type");
    return -1;
  }
  switch (self->dtype) {
    ALL_TYPES(GEN_INIT_CASE)

    case DTYPE_STRING: {
      char** array = (char**)PyMem_Malloc(self->size * sizeof(char*));
      if (!array) return -1;
      for (Py_ssize_t i = 0; i < self->size; i++) {
        PyObject* item = PyList_GetItem(input_list, i);
        const char* s = PyUnicode_AsUTF8(item);
        if (!s) {
          PyMem_Free(array);
          return -1;
        }
        array[i] = strdup(s);
      }
      self->data = array;
      break;
    }
  }
  return 0;
}
