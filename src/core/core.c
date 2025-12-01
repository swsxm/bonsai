#include <string.h>

#include "column/column.h"
#include "dataframe/dataframe.h"

PyTypeObject ColumnType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.Column",
    .tp_basicsize = sizeof(ColumnObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A basic C Column.",
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)Column__init__,
    .tp_dealloc = (destructor)Column__dealloc__};

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.DataFrame",
    .tp_basicsize = sizeof(DataFrameObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A basic C DataFrame.",
    .tp_new = PyType_GenericNew,
    .tp_repr = (reprfunc)DataFrame__repr__,
    .tp_init = (initproc)DataFrame__init__,
    .tp_dealloc = (destructor)DataFrame__dealloc__};
