#ifndef COLUMN_H
#define COLUMN_H

#include "../dtype/dtype.h"

typedef struct {
  char* name;
  void* data;
  size_t len;
  Dispatcher* vtable;
} Column;

int Column_init(Column* self, PyObject* col_name, PyObject* values);

#endif
