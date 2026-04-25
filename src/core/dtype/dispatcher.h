#ifndef DISPATCHER_H
#define DISPATCHER_H

typedef struct Dispatcher {
  char *name;
} Dispatcher;

extern const Dispatcher DISP_INT;
extern const Dispatcher DISP_BOOL;
extern const Dispatcher DISP_STRING;
extern const Dispatcher DISP_CHAR;
extern const Dispatcher DISP_FLOAT;

#endif
