#include <Python.h>
#include "../column.h"
#include "../../dtype/dtype.h"


int Column_init(Column* self, PyObject* col_name, PyObject* values) {

    if (!PyList_Check(values)) {
        PyErr_SetString(PyExc_TypeError, "Column data must be a list.");
        return -1;
    }

    Py_ssize_t list_size = PyList_Size(values);
    if (list_size == 0) {
        PyErr_SetString(PyExc_ValueError, "Cannot infer dtype from empty list.");
        return -1;
    }

    PyObject* first_elem = PyList_GetItem(values, 0);
    if (first_elem == NULL) return -1; 

    if (PyBool_Check(first_elem)) {
        self->dtype = DTYPE_BOOL;
    } else if (PyFloat_Check(first_elem)) {
        self->dtype = DTYPE_FLOAT;
    } else if (PyLong_Check(first_elem)) {
        self->dtype = DTYPE_INT;
    } else if (PyUnicode_Check(first_elem)) {
        if (PyUnicode_GetLength(first_elem) == 1) {
            self->dtype = DTYPE_CHAR;
        } else {
            self->dtype = DTYPE_STRING;
        }
    } else {
        PyErr_Format(PyExc_TypeError, "Unsupported dtype in column.");
        return -1;
    }

    self->name = strdup(PyUnicode_AsUTF8(col_name));
    self->len = list_size;
    const Dispatcher* disp = dispatcher_registry[self->dtype];
    
    self->data = malloc(disp->size * self->len);
    if (self->data == NULL) {
        PyErr_NoMemory();
        return -1;
    }

    for (Py_ssize_t i = 0; i < self->len; i++) {
        void* target_address = (char*)self->data + (i * disp->size);
        PyObject* item = PyList_GetItem(values, i);
        
        disp->set(target_address, item);
    }

    return 0;
}