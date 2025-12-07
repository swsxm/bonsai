#include <Python.h>

#include "../../core.h"

PyObject* DataFrame__add__(PyObject* self, PyObject* args) {
  PyObject* left_col_name;
  PyObject* right_col_name;
  PyObject* new_col_name;

  if (!PyArg_ParseTuple(args, "OOO", &left_col_name, &right_col_name,
                        &new_col_name)) {
    return NULL;
  }

  DataFrameObject* df = (DataFrameObject*)self;

  ColumnObject* left_col = DataFrame_FindCol(self, left_col_name);
  ColumnObject* right_col = DataFrame_FindCol(self, right_col_name);

  if ((left_col == NULL) || (right_col == NULL)) {
    PyErr_SetString(PyExc_KeyError,
                    "One or both columns not found in DataFrame");
    return NULL;
  }

  if (left_col->dtype != right_col->dtype) {
    PyErr_SetString(PyExc_TypeError,
                    "Columns must be of the same dtype to add");
    return NULL;
  }

  if (left_col->size != right_col->size) {
    PyErr_SetString(PyExc_ValueError, "Columns must be the same length");
    return NULL;
  }

  void* new_data = NULL;
  size_t count = left_col->size;

  switch (left_col->dtype) {
    case DTYPE_INT: {
      int* result_array = PyMem_New(int, count);

      if (result_array == NULL) {
        return NULL;
      }

      int* left_data = (int*)left_col->data;
      int* right_data = (int*)right_col->data;

      for (size_t i = 0; i < count; i++) {
        result_array[i] = left_data[i] + right_data[i];
      }

      new_data = result_array;
      break;
    }
    default:
      PyErr_SetString(PyExc_NotImplementedError,
                      "This dtype is not supported for addition");
      return NULL;
  }

  if (DataFrame_InsertColumn(df, new_col_name, new_data, left_col->dtype,
                             count) < 0) {
    free(new_data);
    return NULL;
  }

  Py_RETURN_NONE;
}
