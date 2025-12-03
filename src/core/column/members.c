#include <structmember.h>

#include "column.h"

PyMemberDef Column_members[] = {
    {"name", T_OBJECT_EX, offsetof(ColumnObject, name), READONLY,
     "Name of the column"},
    {"size", T_PYSSIZET, offsetof(ColumnObject, size), READONLY,
     "Number of elements"},
    {"dtype", T_INT, offsetof(ColumnObject, dtype), READONLY,
     "Internal Data Type"},
    {NULL}};
