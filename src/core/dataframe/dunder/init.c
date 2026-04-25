#include <dataframe.h>


int DataFrame_init(DataFrame *self, PyObject *args, PyObject *kwds) {
    PyObject *input_df_dict = NULL; 

    static char *kwlist[] = {"input_df_dict", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Oi", kwlist, 
                                     &input_df_dict)) {
        return -1; 
    }

    if (!PyDict_Check(input_df_dict)) {
        PyErr_SetString(PyExc_TypeError, "The argument must be a dictionary.");
        return -1;
    }

    PyObject *key, *value;
    Py_ssize_t pos = 0;
    Py_ssize_t i = 0;
    
    self->columns = (Column**) malloc(sizeof(Column*) * PyDict_Size(input_df_dict));

    while (PyDict_Next(input_df_dict, &pos, &key, &value)) {
        self->columns[i] = (Column*) malloc(sizeof(Column));
        if (!PyUnicode_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "The keys of the dictionary has to be of type string.");
        }
        Column__init__(self->columns[i], input_df_dict);
        i++;
    }
    
    return 0; 
}