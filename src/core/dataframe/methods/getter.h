#ifndef GETTER_H
#define GETTER_H

#include <Python.h>

PyObject* get_dtype(PyObject* df, PyObject* args, PyObject* kwds);
PyObject* get_value(PyObject* df, PyObject* args, PyObject* kwds);
PyObject* get_name(PyObject* df, PyObject* args, PyObject* kwds);

#endif GETTER_H