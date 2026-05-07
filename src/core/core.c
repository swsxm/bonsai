#include <Python.h>
#include <structmember.h>
#include "core.h"

static PyMemberDef DataFrame_members[] = {
    {"col_count", T_PYSSIZET, offsetof(DataFrame, col_count), READONLY, "Number of columns"},
    {"row_count", T_PYSSIZET, offsetof(DataFrame, row_count),    READONLY, "Number of rows"},
    {NULL}  
};

static PyMethodDef DataFrame_methods[] = {
    {
        "get_dtype", 
        (PyCFunction)get_dtype, 
        METH_VARARGS | METH_KEYWORDS, 
        "Get column dtype by index."
    },
    {
        "get_value", 
        (PyCFunction)get_value, 
        METH_VARARGS | METH_KEYWORDS, 
        "Get value by column and row index."
    },
    {
        "get_name", 
        (PyCFunction)get_name, 
        METH_VARARGS | METH_KEYWORDS, 
        "Get column name by index."
    },
    {
        "get_shape", 
        (PyCFunction)get_shape, 
        METH_NOARGS, 
        "Get shape."
    },
    {NULL, NULL, 0, NULL} 
};

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "bonsai.DataFrame",
    .tp_doc = "Bonsai DataFrame implementation.",
    .tp_basicsize = sizeof(DataFrame),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)DataFrame_init,
    .tp_dealloc =(destructor)DataFrame_dealloc,
    .tp_methods = DataFrame_methods,
    .tp_members = DataFrame_members,
};