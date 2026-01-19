#include "core.h"

static struct PyModuleDef bonsaimodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "bonsai._core._DataFrame",
    .m_doc = "Bonsai C extension.",
    .m_size = -1,
    .m_methods = NULL,
};

PyMODINIT_FUNC PyInit__core(void) {
  PyObject* m;
  printf("DEBUG: tp_name is %s\n", DataFrameType.tp_name);

  if (PyType_Ready(&DataFrameType) < 0) return NULL;

  m = PyModule_Create(&bonsaimodule);
  if (m == NULL) return NULL;

  Py_INCREF(&DataFrameType);
  if (PyModule_AddObject(m, "DataFrame", (PyObject*)&DataFrameType) < 0) {
    Py_DECREF(&DataFrameType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
