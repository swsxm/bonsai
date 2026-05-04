#include "Python.h"
#include "../dataframe.h"
#include "../../column/column.h"

void DataFrame_dealloc(PyObject* df) {
    DataFrame* self = (DataFrame*) df;

    if (self->columns != NULL) {
        for (int i = 0; i < self->col_count; i++) {
            Column_dealloc(self->columns[i]);
        }
        free(self->columns);
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}