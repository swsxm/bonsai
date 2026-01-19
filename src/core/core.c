#include "core.h"

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.DataFrame",
    .tp_doc = "Bonsai DataFrame implementation.",
    .tp_basicsize = sizeof(DataFrame),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
};
