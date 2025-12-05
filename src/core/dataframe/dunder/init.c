#include <Python.h>

#include "core.h"

int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwgs) {
  PyObject* input_dict;
  if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &input_dict)) return -1;

  self->columns = PyList_New(0);
  if (self->columns == NULL) return -1;

  PyObject *key, *value;
  Py_ssize_t pos = 0;

  Py_ssize_t target_length = -1;

  while (PyDict_Next(input_dict, &pos, &key, &value)) {
    Py_ssize_t current_len = PyObject_Size(value);

    if (current_len < 0) {
      return -1;
    }

    if (target_length == -1) {
      target_length = current_len;
    } else if (current_len != target_length) {
      PyErr_Format(
          PyExc_ValueError,
          "All columns must be the same length. Expected %zd, got %zd.",
          target_length, current_len);
      return -1;
    }

    PyObject* column =
        PyObject_CallFunction((PyObject*)&ColumnType, "OO", key, value);
    if (column == NULL) {
      return -1;
    }

    int ret = PyList_Append(self->columns, column);
    Py_DECREF(column);
    if (ret < 0) return -1;
  }

  if (target_length == -1) {
    self->num_columns = 0;
  } else {
    self->num_columns = PyList_GET_SIZE(self->columns);
  }

  return 0;
}
