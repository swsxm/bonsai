#include <Python.h>

#include "../dataframe.h"

void DataFrame__dealloc__(DataFrameObject* self) {
  if (self->data) {
    if (self->dtype == DTYPE_STRING) {
      char** arr = (char**)self->data;
      for (Py_ssize_t i = 0; i < self->size; i++) free(arr[i]);
    }
    PyMem_Free(self->data);
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}
