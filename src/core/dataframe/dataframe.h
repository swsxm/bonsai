#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "../core.h"

typedef struct {
  PyObject_HEAD
  Column** columns;
  Py_ssize_t row_count;
  Py_ssize_t col_count;
} DataFrame;

int DataFrame_init(PyObject*, PyObject*, PyObject*);

#endif
