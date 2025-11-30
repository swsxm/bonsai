#include <Python.h>

#include "core.h"

static struct PyModuleDef core_module = {PyModuleDef_HEAD_INIT, "_core", NULL,
                                         -1, NULL};

int register_type(PyObject* m, const char* name, PyTypeObject* type) {
  if (PyType_Ready(type) < 0) {
    return -1;
  }

  Py_INCREF(type);

  if (PyModule_AddObject(m, name, (PyObject*)type) < 0) {
    Py_DECREF(type);
    return -1;
  }

  return 0;
}

PyMODINIT_FUNC PyInit__core(void) {
  PyObject* m;

  m = PyModule_Create(&core_module);
  if (m == NULL) return NULL;

  if (register_type(m, "DataFrame", &DataFrameType) < 0) {
    Py_DECREF(m);
    return NULL;
  }

  if (register_type(m, "Column", &ColumnType) < 0) {
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
