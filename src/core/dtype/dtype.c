#include "dtype.h"

extern const Dispatcher* const dispatcher_registry[DTYPE_COUNT] = {
    [DTYPE_BOOL]   = &DISP_BOOL,
    [DTYPE_FLOAT]  = &DISP_FLOAT,
    [DTYPE_INT]    = &DISP_INT,
    [DTYPE_CHAR]   = &DISP_CHAR,
    [DTYPE_STRING] = &DISP_STRING
};

extern const char* const dtype_names[DTYPE_COUNT] = {
    [DTYPE_BOOL]   = "bool",
    [DTYPE_FLOAT]  = "float",
    [DTYPE_INT]    = "int",
    [DTYPE_CHAR]   = "char",
    [DTYPE_STRING] = "string"
};