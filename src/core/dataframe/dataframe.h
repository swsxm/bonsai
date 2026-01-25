#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "../core.h"

typedef struct {
  Column** columns;
  Py_ssize_t row_count;
  Py_ssize_t col_count;
} DataFrame;

PyObject* DataFrame__init__(DataFrame*, PyObject*);

#endif
