#include <Python.h>
#include "../dataframe.h"
#include <stdbool.h>

PyObject* add(PyObject* df, PyObject* args, PyObject* kwds) {
    DataFrame* self = (DataFrame*) df;

    char* col1_name;
    char* col2_name;
    char* out_col_name; 

    static char *kwlist[] = {"col1", "col2", "col_out", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sss", kwlist, &col1_name, &col2_name, &out_col_name)) {
        return NULL;
    }

    int idx1 = -1, idx2 = -1, idx_out = -1;

    for (int i = 0; i < self->col_count; i++) {
        char* current_name = self->columns[i]->name;

        if (idx1 == -1 && strcmp(current_name, col1_name) == 0) idx1 = i;
        if (idx2 == -1 && strcmp(current_name, col2_name) == 0) idx2 = i;
        if (idx_out == -1 && strcmp(current_name, out_col_name) == 0) idx_out = i;
    }

    if (idx1 == -1 || idx2 == -1 || idx_out == -1) {
        PyErr_SetString(PyExc_ValueError, "One or more columns not found in DataFrame.");
        return NULL;
    }

    Column* col1 = self->columns[idx1];
    Column* col2 = self->columns[idx2];
    Column* out_col = self->columns[idx_out];

    if (strcmp(col1->vtable->dtype_name, col2->vtable->dtype_name) != 0) {
        PyErr_Format(PyExc_TypeError, 
            "Dtype mismatch: Cannot add '%s' to '%s'.", 
            col1->vtable->dtype_name);
        return NULL;
    }

    // WIP
    Py_RETURN_NONE; 
}