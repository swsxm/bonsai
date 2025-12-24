#include <Python.h>

#include "../../core.h"

PyObject* DataFrameAdd(PyObject* self, PyObject* args) {
  PyObject *left_col_name, *right_col_name, *new_col_name;

  if (!PyArg_ParseTuple(args, "OOO", &left_col_name, &right_col_name,
                        &new_col_name)) {
    return NULL;
  }

  DataFrameObject* df = (DataFrameObject*)self;
  ColumnObject* left_col = DataFrame_FindCol(df, left_col_name);
  ColumnObject* right_col = DataFrame_FindCol(df, right_col_name);

  if (!left_col || !right_col) {
    PyErr_SetString(PyExc_KeyError, "One or both columns not found");
    return NULL;
  }

  if (left_col->dtype != right_col->dtype ||
      left_col->size != right_col->size) {
    PyErr_SetString(PyExc_ValueError,
                    "Columns must have the same dtype and size");
    return NULL;
  }

  void* new_data = NULL;
  size_t count = left_col->size;

  switch (left_col->dtype) {
    case DTYPE_INT: {
      long long* res = PyMem_New(long long, count);
      if (!res) return PyErr_NoMemory();

      long long* l = (long long*)left_col->data;
      long long* r = (long long*)right_col->data;

      for (size_t i = 0; i < count; i++) {
        res[i] = l[i] + r[i];
      }
      new_data = res;
      break;
    }
    case DTYPE_FLOAT: {
      double* res = PyMem_New(double, count);
      if (!res) return PyErr_NoMemory();

      double* l = (double*)left_col->data;
      double* r = (double*)right_col->data;

      for (size_t i = 0; i < count; i++) {
        res[i] = l[i] + r[i];
      }
      new_data = res;
      break;
    }
    default:
      PyErr_SetString(PyExc_NotImplementedError, "Dtype not supported");
      return NULL;
  }

  ColumnObject* new_col = PyObject_New(ColumnObject, &ColumnType);
  if (!new_col) {
    PyMem_Free(new_data);
    return NULL;
  }

  Py_INCREF(new_col_name);
  new_col->name = new_col_name;
  new_col->dtype = left_col->dtype;
  new_col->size = count;
  new_col->data = new_data;

  if (PyList_Append(df->columns, (PyObject*)new_col) < 0) {
    Py_DECREF(new_col_name);
    PyMem_Free(new_data);
    Py_DECREF(new_col);
    return NULL;
  }

  Py_DECREF(new_col);
  df->num_columns++;

  Py_INCREF(self);
  return (PyObject*)self;
}
