#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <Python.h>

extern PyTypeObject DataFrameType;
typedef struct {
  PyObject_HEAD PyObject* columns;
  Py_ssize_t num_columns;
} DataFrameObject;

extern PyMemberDef DataFrame_members[];

void DataFrame__dealloc__(DataFrameObject* self);
int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwds);
PyObject* DataFrameGetItem(DataFrameObject* self, PyObject* args,
                           PyObject* kwds);
PyObject* DataFrameGetDtype(DataFrameObject* self, PyObject* args,
                            PyObject* kwds);
PyObject* DataFrameSelect(DataFrameObject* self, PyObject* args);
PyObject* DataFrame_CreateFromColumnList(PyObject* column_list,
                                         PyTypeObject* type);
ColumnObject* DataFrame_FindCol(DataFrameObject* self, PyObject* col_name);

#endif
