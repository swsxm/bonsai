#include <Python.h>

#include "core.h"

void DataFrame__dealloc__(DataFrameObject* self) {
  if (self->columns) {
    Py_XDECREF(self->columns);
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}
