#include <Python.h>
#include "../dataframe.h"
#include "../../column/column.h"

PyObject* get_dtype(PyObject* df, PyObject* args, PyObject* kwds) {
    DataFrame* self = (DataFrame*) df;
    
    Py_ssize_t col_index; 
    
    static char *kwlist[] = {"index", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &col_index)) {
        return NULL; 
    }

    if (col_index < 0 || col_index >= self->col_count) {
        PyErr_SetString(PyExc_IndexError, "Column index out of range.");
        return NULL; 
    }

    Column* col = self->columns[col_index];
    
    return PyUnicode_FromString(dtype_names[col->dtype]);
}

PyObject* get_value(PyObject* df, PyObject* args, PyObject* kwds) {
    DataFrame* self = (DataFrame*) df;
    
    Py_ssize_t row_index;
    Py_ssize_t col_index; 
    
    static char *kwlist[] = {"row_index", "col_index", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &row_index, &col_index)) {
        return NULL; 
    }

    if (col_index < 0 || col_index >= self->col_count) {
        PyErr_SetString(PyExc_IndexError, "Column index out of range.");
        return NULL; 
    }

    if (row_index < 0 || row_index >= self->row_count) {
        PyErr_SetString(PyExc_IndexError, "Row index out of range.");
        return NULL; 
    }

    Column* col = self->columns[col_index];
    return dispatcher_registry[col->dtype]->get(col, row_index);
}

PyObject* get_name(PyObject* df, PyObject* args, PyObject* kwds) {
    DataFrame* self = (DataFrame*) df;
    
    Py_ssize_t col_index; 
    static char *kwlist[] = {"index", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &col_index)) {
        return NULL; 
    }

    if (col_index < 0 || col_index >= self->col_count) {
        PyErr_SetString(PyExc_IndexError, "Column index out of range.");
        return NULL; 
    }
    Column* col = self->columns[col_index];
    const char* name = col->name;
    
    return PyUnicode_FromString(name);
}

PyObject* get_shape(PyObject* df) {
    DataFrame* self = (DataFrame*) df;
    return Py_BuildValue("(ii)", self->col_count, self->row_count);
}