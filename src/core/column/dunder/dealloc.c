#include <Python.h>

#include "core.h"

void Column__dealloc__(ColumnObject* self) {
  if (self->data != NULL) {
    if (self->dtype == DTYPE_STRING) {
      char** str_data = (char**)self->data;
      for (int i = 0; i < self->size; i++) {
        if (str_data[i]) free(str_data[i]);
      }
    }
    PyMem_Free(self->data);
    self->data = NULL;
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}
