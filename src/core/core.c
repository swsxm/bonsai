#include <string.h>

#include "column/column.h"
#include "dataframe/dataframe.h"

static PyMethodDef DataFrame_methods[] = {
    {"get_item", (PyCFunction)DataFrameGetItem, METH_VARARGS,
     "Get the column item at index i."},
    {"get_dtype", (PyCFunction)DataFrameGetDtype, METH_VARARGS,
     "Get the column item at index i."},
    {NULL, NULL, 0, NULL}};

PyTypeObject ColumnType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.Column",
    .tp_basicsize = sizeof(ColumnObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A basic C Column.",
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)Column__init__,
    .tp_dealloc = (destructor)Column__dealloc__,
    .tp_members = Column_members};

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.DataFrame",
    .tp_basicsize = sizeof(DataFrameObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "A basic C DataFrame.",
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)DataFrame__init__,
    .tp_dealloc = (destructor)DataFrame__dealloc__,
    .tp_methods = DataFrame_methods,
    .tp_members = DataFrame_members};
