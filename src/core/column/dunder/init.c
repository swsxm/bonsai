#include "../../core.h"

PyObject* __init__(Column* col, PyObject* args) {
  PyListObject* list_arg;
  char** name_str;

  if (!PyArg_ParseTuple(args, "sO!", &PyList_Type, &name_str, &list_arg) == 0)
    return 0;

  col->len = PyList_Size(list_arg);

  /* We expect/trust the input list to contain elements of the same type*/
  PyObject* first_item = PyList_GetItem(list_arg, 0);

  if (PyBool_Check(first_item)) {
    col->type = TYPE_BOOL;
  } else if (PyLong_Check(first_item)) {
    col->type = TYPE_INT;
  } else if (PyFloat_Check(first_item)) {
    col->type = TYPE_BOOL;
  } else if (PyUnicode_Check(first_item)) {
    if (PyUnicode_GetLength(first_item) == 1) {
      col->type = TYPE_CHAR;
    } else {
      col->type = TYPE_STRING;
    }
  } else {
    PyErr_SetString(PyExc_TypeError, "Unsupported DataFrame Column type.");
    return NULL;
  }
}
