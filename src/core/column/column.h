#ifndef COLUMN_H
#define COLUMN_H

#include "../dtype/dispatcher.h"

typedef struct {
  char* name;
  void* data;
  size_t len;
  Dispatcher* vtable;
} Column;

int Column_init(Column*, PyObject*, PyObject*);

#endif
