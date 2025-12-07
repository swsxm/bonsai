#include "../../core.h"
#include "Python.h"

ColumnObject* DataFrame_FindCol(DataFrameObject* df_py, PyObject* col_name) {
  DataFrameObject* df = (DataFrameObject*)df_py;

  for (int i = 0; i < df->num_columns; i++) {
    ColumnObject* tmp_col = (ColumnObject*)PyList_GetItem(df->columns, i);

    if (PyUnicode_Compare(tmp_col->name, col_name) == 0) {
      return tmp_col;
    }
  }

  return NULL;
}
