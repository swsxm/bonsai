#ifndef DTYPE_H 
#define DTYPE_H 

#include <Python.h>

void* int_set(void* dest, PyObject* val);
void* bool_set(void* dest, PyObject* val);
void* string_set(void* dest, PyObject* val);
void* char_set(void* dest, PyObject* val);
void* float_set(void* dest, PyObject* val);

PyObject* int_get(PyObject*, Py_ssize_t);
PyObject* bool_get(PyObject*, Py_ssize_t);
PyObject* string_get(PyObject*, Py_ssize_t);
PyObject* char_get(PyObject*, Py_ssize_t);
PyObject* float_get(PyObject*, Py_ssize_t);

typedef enum {
    DTYPE_BOOL,  
    DTYPE_FLOAT, 
    DTYPE_INT,
    DTYPE_CHAR,
    DTYPE_STRING,
    DTYPE_COUNT
} DTYPE;

typedef struct Dispatcher {
  Py_ssize_t size;
  void (*set)(void*, PyObject*);
  PyObject* (*get)(PyObject*, Py_ssize_t);
  char* dtype_name;
} Dispatcher;

extern const Dispatcher DISP_INT;
extern const Dispatcher DISP_BOOL;
extern const Dispatcher DISP_STRING;
extern const Dispatcher DISP_CHAR;
extern const Dispatcher DISP_FLOAT;

extern const char* const dtype_names[DTYPE_COUNT]; 
extern const Dispatcher* const dispatcher_registry[DTYPE_COUNT];

#endif