#ifndef GENERIC_H 
#define GENERIC_H 

#include <Python.h>

void* int_set(void* dest, PyObject* val);
void* bool_set(void* dest, PyObject* val);
void* string_set(void* dest, PyObject* val);
void* char_set(void* dest, PyObject* val);
void* float_set(void* dest, PyObject* val);

PyObject* int_get(PyObject*, Py_ssize_t);
PyObject* bool_get(PyObject*, Py_ssize_t);
PyObject* string_get(PyObject*, Py_ssize_t);
PyObject* char_get(PyObject*, Py_ssize_t);
PyObject* float_get(PyObject*, Py_ssize_t);

#endif