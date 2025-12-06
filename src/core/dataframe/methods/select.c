#include <Python.h>

#include "../../core.h"

PyObject* DataFrameSelect(DataFrameObject* self, PyObject* args) {
  PyObject* input_arg;

  if (!PyArg_ParseTuple(args, "O", &input_arg)) {
    return NULL;
  }

  PyObject* new_col_list = PyList_New(0);

  if (PyUnicode_Check(input_arg)) {
    for (int i = 0; i < self->num_columns; i++) {
      ColumnObject* col = (ColumnObject*)PyList_GetItem(self->columns, i);

      int compare = PyObject_RichCompareBool(col->name, input_arg, Py_EQ);

      if (compare == 1) {
        PyList_Append(new_col_list, (PyObject*)col);
      }
    }
  }

  else if (PyList_Check(input_arg)) {
    // WIP
  }

  PyObject* result_df =
      DataFrame_CreateFromColumnList(new_col_list, Py_TYPE(self));
  Py_DECREF(new_col_list);

  return result_df;
}
