#ifndef COLUMN_H
#define COLUMN_H
#include "core.h"

#define ALL_TYPES(X)                                                      \
  X(DTYPE_FLOAT, double, PyFloat_AsDouble, PyFloat_FromDouble, "%.6g")    \
  X(DTYPE_INT, long long, PyLong_AsLongLong, PyLong_FromLongLong, "%lld") \
  X(DTYPE_BOOL, char, PyObject_IsTrue, PyBool_FromLong, "%d")

typedef enum {
#define GENERATE_ENUM(NAME, T, P2C, C2P, FMT) NAME,
  ALL_TYPES(GENERATE_ENUM)
#undef GENERATE_ENUM
      DTYPE_STRING
} ColumnDType;

typedef struct {
  PyObject_HEAD void* data;
  Py_ssize_t size;
  ColumnDType dtype;
  PyObject* name;
} ColumnObject;

extern PyTypeObject ColumnType;
extern PyMemberDef Column_members[];

void Column__dealloc__(ColumnObject* self);
int Column__init__(ColumnObject* self, PyObject* args, PyObject* kwds);
extern PyObject* ColumnGetItem(ColumnObject* self, int row_num);

#endif
