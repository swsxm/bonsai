#include "../../core.h"

PyObject* DataFrame__init__(DataFrame* df, PyObject* args) {
  PyObject* dict_arg;
  if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict_arg)) return NULL;

  Py_ssize_t d_size = PyDict_Size(dict_arg);
  df->col_count = d_size;

  df->columns = malloc(d_size * sizeof(Column*));
  if (df->columns == NULL) return PyErr_NoMemory();

  Py_ssize_t pos = 0;
  PyObject *key, *value;
  int i = 0;

  while (PyDict_Next(dict_arg, &pos, &key, &value)) {
    if (PyUnicode_Check(key) && PyList_Check(value)) {
      Py_ssize_t current_list_len = PyList_Size(value);

      if (i == 0) {
        df->row_count = current_list_len;
      } else if (current_list_len != df->row_count) {
        PyErr_SetString(PyExc_ValueError,
                        "Expected value lists of same length.");
        return NULL;
      }

      const char* col_name = PyUnicode_AsUTF8(key);
      Column* col = Column__init__(col_name, value);

      if (col == NULL) return NULL;

      df->columns[i] = col;
      i++;
    } else {
      PyErr_SetString(PyExc_TypeError, "Expected Dict[str, list].");
      return NULL;
    }
  }

  Py_RETURN_NONE;
}
