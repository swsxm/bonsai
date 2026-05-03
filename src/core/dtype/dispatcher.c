#include <stdbool.h>
#include <stdint.h>
#include "dispatcher.h"
#include "generic.h"

const Dispatcher DISP_INT = {
    .size = sizeof(int64_t),
    .set  = int_set, 
    .get  = int_get,
    .dtype_name = "INT64"
};

const Dispatcher DISP_BOOL = {
    .size = sizeof(bool),
    .set  = bool_set,
    .get  = bool_get,
    .dtype_name = "BOOL"
};

const Dispatcher DISP_STRING = {
    .size = sizeof(char*),
    .set = string_set,
    .get = string_get,
    .dtype_name = "STRING"
};

const Dispatcher DISP_CHAR = {
    .size = sizeof(char),
    .set  = char_set,
    .get  = char_get,
    .dtype_name = "CHAR"
};

const Dispatcher DISP_FLOAT = {
    .size = sizeof(double),
    .set  = float_set, 
    .get  = float_get,
    .dtype_name = "FLOAT"
};