#include <Python.h>
#include "../column.h"
#include "../../dtype/dtype.h"

void Column_dealloc(Column* col) {
    if (col == NULL) return;
    
    if (col->name != NULL) {
        free(col->name);
    }
    
    if (col->data != NULL) {
        if (col->dtype == DTYPE_STRING) {
            for (size_t i = 0; i < col->len; i++) {
                char* str = ((char**)col->data)[i];
                if (str != NULL) {
                    free(str);
                }
            }
        }
        free(col->data);
    }
    
    free(col);
}