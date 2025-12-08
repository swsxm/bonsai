#include <Python.h>
#include <structmember.h>

#include "../core.h"

PyMemberDef DataFrame_members[] = {
    {"columns", T_OBJECT_EX, offsetof(DataFrameObject, columns), READONLY,
     "Internal list of Column objects.\n"
     "\n"
     "Type:\n"
     "    list[Column]: A list containing the raw column wrappers."},
    {"num_columns", T_PYSSIZET, offsetof(DataFrameObject, num_columns),
     READONLY,
     "The number of rows in the DataFrame.\n"
     "\n"
     "Type:\n"
     "    int: The total count of rows (equivalent to len(df))."},
    {NULL}};
