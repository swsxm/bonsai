#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "../core.h"

typedef struct {
  Column* columns;
  int row_len;
  int col_len;
} DataFrame;

#endif
