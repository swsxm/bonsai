#include <Python.h>
#include <stdio.h>
#include <string.h>

#include "core.h"

#define GEN_MEASURE_CASE(NAME, C_TYPE, P2C, C2P, FMT) \
  case NAME: {                                        \
    C_TYPE* raw = (C_TYPE*)col->data;                 \
    C_TYPE val = raw[row_idx];                        \
    char temp[64];                                    \
    int l = snprintf(temp, sizeof(temp), FMT, val);   \
    if (l > max_width) max_width = l;                 \
    break;                                            \
  }

PyObject* DataFrame__repr__(DataFrameObject* self) {
  PyObject* lines = PyList_New(0);
  if (!lines) return NULL;

  Py_ssize_t* col_widths = PyMem_Malloc(self->num_columns * sizeof(Py_ssize_t));
  if (!col_widths) {
    Py_DECREF(lines);
    return NULL;
  }

  Py_ssize_t sum_col_widths = 0;

  for (int i = 0; i < self->num_columns; i++) {
    PyObject* item = PyList_GetItem(self->columns, i);
    ColumnObject* col = (ColumnObject*)item;

    Py_ssize_t name_len = PyObject_Length(col->name);
    int max_width = (int)name_len;

    Py_ssize_t boundary = (col->size > 5) ? 5 : col->size;

    for (int row_idx = 0; row_idx < boundary; row_idx++) {
      switch (col->dtype) { ALL_TYPES(GEN_MEASURE_CASE) }
    }
    col_widths[i] = max_width;
    sum_col_widths += max_width;
  }

  int visual_width = sum_col_widths + (self->num_columns - 1) * 3 + 4;
  size_t buf_size = (visual_width * 4) + 1;
  char* buffer = PyMem_Malloc(buf_size);
  char* p;

  p = buffer;
  strcpy(p, "┌");
  p += strlen("┌");

  for (int i = 0; i < self->num_columns; i++) {
    int w = (int)col_widths[i];
    for (int k = 0; k < w + 2; k++) {
      strcpy(p, "─");
      p += strlen("─");
    }
    if (i < self->num_columns - 1) {
      strcpy(p, "┬");
      p += strlen("┬");
    }
  }
  strcpy(p, "┐");
  p += strlen("┐");
  *p = '\0';

  PyList_Append(lines, PyUnicode_FromString(buffer));

  p = buffer;
  strcpy(p, "│ ");
  p += strlen("│ ");

  for (int i = 0; i < self->num_columns; i++) {
    PyObject* item = PyList_GetItem(self->columns, i);
    ColumnObject* col = (ColumnObject*)item;

    PyObject* padded =
        PyObject_CallMethod(col->name, "ljust", "i", (int)col_widths[i]);

    if (padded) {
      const char* s = PyUnicode_AsUTF8(padded);
      strcpy(p, s);
      p += strlen(s);
      Py_DECREF(padded);
    }

    if (i < self->num_columns - 1) {
      strcpy(p, " │ ");
      p += strlen(" │ ");
    }
  }
  strcpy(p, " │");
  p += strlen(" │");
  *p = '\0';

  PyList_Append(lines, PyUnicode_FromString(buffer));

  PyMem_Free(buffer);
  PyMem_Free(col_widths);

  PyObject* newline = PyUnicode_FromString("\n");
  PyObject* result = PyUnicode_Join(newline, lines);

  Py_DECREF(newline);
  Py_DECREF(lines);

  return result;
}
