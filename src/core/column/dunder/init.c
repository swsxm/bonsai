#include "../../core.h"

PyObject* __init__(Column* col, char* col_name, PyObject* values) {
  // Optimistic strict policy
  // We expect the column to contain the same dtype

  PyObject* first_elem =  PyList_GetItem(0);
  if (PyBool_Check(first_elem)) {
    col->type = "BOOL";
    // col->vtable =  tbd
  }
  else if (PyNumber_Check(first_elem)) {

  }

  else if (PyFloat_Check(first_elem)) {

  }

  else if () {

  }
  else {
    return PyErr_Occurred("error");
  }

  now we would have to malloc for data 
  and iterate over our array set valeus
  set col len and row len

}
