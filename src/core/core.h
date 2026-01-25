#ifndef CORE_H
#define CORE_H

#include <Python.h>

#include "column/column.h"
#include "dataframe/dataframe.h"
#include "dtype/dispatcher.h"

extern PyTypeObject DataFrameType;
extern PyTypeObject ColumnType;

#endif CORE_H
