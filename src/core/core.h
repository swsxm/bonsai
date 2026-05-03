#ifndef CORE_H
#define CORE_H

#include <Python.h>

#include "dtype/generic.h"
#include "dtype/dispatcher.h"
#include "column/column.h"
#include "dataframe/dataframe.h"

extern PyTypeObject DataFrameType;

#endif
