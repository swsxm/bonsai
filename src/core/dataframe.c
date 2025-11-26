#include "dataframe.h"

#include <string.h>

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.DataFrame",
    .tp_basicsize = sizeof(DataFrameObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A basic C DataFrame (single list)",
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)DataFrame__init__,
    .tp_dealloc = (destructor)DataFrame__dealloc__,
    .tp_repr = (reprfunc)DataFrame__repr__};
