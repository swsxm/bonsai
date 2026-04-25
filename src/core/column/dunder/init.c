#include "../../core.h"

PyObject* Column__init__(Column* self, char* col_name, PyObject* values) {

  // Optimistic strict policy
  // We expect the column to contain the same dtype
  PyObject* first_elem =  PyList_GetItem(values, 0);

  // Order matters
  if (PyBool_Check(first_elem)) {
    self->vtable = DISP_BOOL;
  }
  else if (PyFloat_Check(first_elem)) {
    self->vtable = DISP_FLOAT;
  }
  else if (PyLong_Check(first_elem)) {
    self->vtable = DISP_INT;
  }
  else if (PyUnicode_Check(first_elem) && PyUnicode_GetLength(first_elem) == 1) {
    self->vtable = DISP_CHAR;
  }
  else if (PyUnicode_Check(first_elem)) {
    self->vtable = DISP_STRING;
  }
  else {
    return PyErr_Format(PyExc_TypeError, "Dtype is not supported for col %s.", *col_name);
  }

  self->name = col_name;
  self->len = PyList_Size(values);
  self->data = malloc(self->vtable->size * self->len);
  for (Py_ssize_t i = 0; i < self->len; i++) {
    void* target_address = self->data + i * self->vtable->size;
    self->vtable->set(target_address, PyList_GetItem(values, i));
  }

}
