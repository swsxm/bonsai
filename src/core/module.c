#include <Python.h>

#include "dataframe.h"

static struct PyModuleDef core_module = {PyModuleDef_HEAD_INIT, "_core", NULL,
                                         -1, NULL};

PyMODINIT_FUNC PyInit__core(void) {
  PyObject* m;

  if (PyType_Ready(&DataFrameType) < 0) {
    return NULL;
  }

  m = PyModule_Create(&core_module);
  if (m == NULL) {
    return NULL;
  }

  Py_INCREF(&DataFrameType);
  if (PyModule_AddObject(m, "DataFrame", (PyObject*)&DataFrameType) < 0) {
    Py_DECREF(&DataFrameType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
