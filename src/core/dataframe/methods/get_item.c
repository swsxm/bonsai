#include <Python.h>

#include "../../core.h"

PyObject* DataFrameGetItem(DataFrameObject* self, PyObject* args,
                           PyObject* kwds) {
  int row_num;
  int col_num;

  PyObject* col_py;
  ColumnObject* col;

  if (!PyArg_ParseTuple(args, "ii", &row_num, &col_num)) {
    return NULL;
  }
  col_py = PyList_GetItem(self->columns, col_num);
  col = (ColumnObject*)col_py;
  return ColumnGetItem(col, row_num);
}
