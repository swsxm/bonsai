#include <Python.h>

#include "../../core.h"

PyObject* DataFrame_CreateFromColumnList(PyObject* column_list,
                                         PyTypeObject* type) {
  DataFrameObject* new_df = (DataFrameObject*)type->tp_alloc(type, 0);

  if (!new_df) return NULL;

  Py_INCREF(column_list);
  new_df->columns = column_list;
  new_df->num_columns = PyList_Size(column_list);

  if (new_df->num_columns > 0) {
    ColumnObject* first_col = (ColumnObject*)PyList_GetItem(column_list, 0);
  } else {
  }

  return (PyObject*)new_df;
}
