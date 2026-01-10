#ifndef COLUMN_H
#define COLUMN_H
#include "../core.h"
#include "Python.h"

typedef struct {
  char* name;
  void* data;
  size_t len;
  size_t element_size;
  Dispatcher vtable;
} Column;

#endif
