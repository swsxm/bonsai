#include "../dataframe.h"

int DataFrame_init(PyObject *df, PyObject *args, PyObject *kwds) {
    PyObject *input_df_dict = NULL; 
    DataFrame* self = (DataFrame*) df;
    static char *kwlist[] = {"data", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &input_df_dict)) {
        return -1; 
    }

    if (!PyDict_Check(input_df_dict)) {
        PyErr_SetString(PyExc_TypeError, "The argument must be a dictionary.");
        return -1;
    }

    PyObject *key, *value;
    Py_ssize_t pos = 0;
    Py_ssize_t i = 0;
    Py_ssize_t dict_size = PyDict_Size(input_df_dict);
    
    self->col_count = dict_size;
    self->row_count = 0;
    self->columns = (Column**) malloc(sizeof(Column*) * dict_size);

    if (self->columns == NULL) {
        PyErr_NoMemory();
        return -1;
    }

    while (PyDict_Next(input_df_dict, &pos, &key, &value)) {
        
        if (!PyUnicode_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "Column names must be strings.");
            return -1;
        }

        Py_ssize_t col_len = PyList_Size(value);
        if (i == 0) {
            self->row_count = col_len;
        } else if (col_len != self->row_count) {
            PyErr_SetString(PyExc_ValueError, "All columns must have equal length.");
            return -1;
        }

        self->columns[i] = (Column*) malloc(sizeof(Column));
        if (self->columns[i] == NULL) {
            PyErr_NoMemory();
            return -1;
        }


        if (Column_init(self->columns[i], key, value) != 0) {
            return -1;
        }
        
        i++;
    }

    return 0; 
}