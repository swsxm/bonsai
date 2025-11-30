#include <Python.h>

#include "../../column/column.h"
#include "../dataframe.h"

int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwgs) {
  PyObject* input_dict;
  if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &input_dict)) return -1;
  self->columns = PyList_New(0);

  PyObject *key, *value;
  Py_ssize_t pos = 0;
  Py_ssize_t i = 0;

  while (PyDict_Next(input_dict, &pos, &key, &value)) {
    PyObject* column =
        PyObject_CallFunction((PyObject*)&ColumnType, "nOO", key, value);
    if (column == NULL) {
      return -1;
    }
    int ret = PyList_Append(self->columns, column);
    Py_DECREF(column);
    if (ret < 0) return -1;
    i++;
  }
  self->num_columns = i;
  return 0;
}
