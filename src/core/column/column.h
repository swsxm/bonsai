#ifndef COLUMN_H
#define COLUMN_H
#include "../core.h"

typedef enum {
  TYPE_BOOL,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_CHAR,
  TYPE_STRING
} ColType;

typedef struct {
  char* name;
  void* data;
  size_t len;
  Dispatcher vtable;
} Column;

PyObject* Column__init__(Column*, PyObject*);

#endif
