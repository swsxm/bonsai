#include <Python.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "../column/column.h"

// SETTERS
void *int_set(void *dest, PyObject *val) {
    int overflow;
    long result = PyLong_AsLongAndOverflow(val, &overflow);
    if (result == -1 && PyErr_Occurred()) return NULL;
    if (overflow != 0 || result > INT_MAX || result < INT_MIN) {
        PyErr_SetString(PyExc_OverflowError, "Value out of range for C int");
        return NULL;
    }
    *(int *)dest = (int)result;
    return dest;
}

void *char_set(void *dest, PyObject *val) {
    int overflow;
    long result = PyLong_AsLongAndOverflow(val, &overflow);
    if (result == -1 && PyErr_Occurred()) return NULL;
    if (overflow != 0 || result > SCHAR_MAX || result < SCHAR_MIN) {
        PyErr_SetString(PyExc_OverflowError, "Value out of range for C char");
        return NULL;
    }
    *(signed char *)dest = (signed char)result;
    return dest;
}

void *float_set(void *dest, PyObject *val) {
    double result = PyFloat_AsDouble(val);
    if (result == -1.0 && PyErr_Occurred()) return NULL;
    *(float *)dest = (float)result;
    return dest;
}


void *bool_set(void *dest, PyObject *val) {
    int truth = PyObject_IsTrue(val);
    if (truth == -1) return NULL;
    *(bool *)dest = (truth != 0);
    return dest;
}


void *string_set(void *dest, PyObject *val) {
    const char *str = PyUnicode_AsUTF8(val);
    if (!str) return NULL;
    
    char *copy = strdup(str); 
    if (!copy) return PyErr_NoMemory();
    
    *(char **)dest = copy;
    return dest;
}

// GETTERS
PyObject* *char_get(PyObject* self, Py_ssize_t row_index) {
    Column* col = (Column*)self;
    char value = ((char*)col->data)[row_index];
    return PyUnicode_FromFormat("%c", value);
}

PyObject* *int_get(PyObject* self, Py_ssize_t row_index) {
    Column* col = (Column*)self;
    long long value = ((long long*)col->data)[row_index];
    return PyLong_FromLongLong(value);
}

PyObject* *float_get(PyObject* self, Py_ssize_t row_index) {
    Column* col = (Column*)self;
    double value = ((double*)col->data)[row_index];
    return PyFloat_FromDouble(value);
}
PyObject* *bool_get(PyObject* self, Py_ssize_t row_index) {
    Column* col = (Column*)self;
    char value = ((char*)col->data)[row_index];
    if (value) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject* *string_get(PyObject* self, Py_ssize_t row_index) {
    Column* col = (Column*)self;
    char* value = ((char**)col->data)[row_index];
    
    if (value == NULL) {
        Py_RETURN_NONE;
    }
    return PyUnicode_FromString(value);
}