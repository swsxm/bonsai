#include "dataframe.h"

#include <Python.h>

static void DataFrame__dealloc__(DataFrameObject* self) {
  if (self->data != NULL) {
    PyMem_Free(self->data);
    self->data = NULL;
  }

  Py_TYPE(self)->tp_free((PyObject*)self);
}

int DataFrame__init__(DataFrameObject* self, PyObject* args, PyObject* kwgs) {
  PyObject* input_list;

  if (!PyArg_ParseTuple(args, "O", &input_list)) {
    return -1;
  }

  if (!PyList_Check(input_list)) {
    PyErr_SetString(PyExc_TypeError, "Input has to be of type list");
    return -1;
  }

  self->size = PyList_Size(input_list);
  self->data = (double*)PyMem_Malloc(self->size * sizeof(double));

  if (self->data == NULL) {
    PyErr_NoMemory();
    return -1;
  }

  PyObject* temp_item;

  for (Py_ssize_t i = 0; i < self->size; i++) {
    temp_item = PyList_GetItem(input_list, i);
    double c_val = PyFloat_AsDouble(temp_item);

    if (PyErr_Occurred()) {
      PyMem_Free(self->data);
      return -1;
    }
    self->data[i] = c_val;
  }
  return 0;
}

PyTypeObject DataFrameType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "bonsai.DataFrame",
    .tp_basicsize = sizeof(DataFrameObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A basic C DataFrame (single list)",
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)DataFrame__init__,
    .tp_dealloc = (destructor)DataFrame__dealloc__,
};
