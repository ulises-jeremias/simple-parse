#ifndef SPARSE_H
#define SPARSE_H

#include <string.h>
#include <stdlib.h>

#include <sparse_default.h>
#include <sparse_inline.h>

#define FLAG_MAX_SIZE 80
#define FLAG_MAX_NUMBER 20

__SPARSE_BEGIN_DECLS

extern char** sparse_allocated_args;
extern int sparse_initialized;
extern int sparse_current_arg;

void sparse_cleanup();
void sparse_init();
char *sparse_flag(char *name, char *defaultValue, int argc, char **argv);

__SPARSE_END_DECLS

#endif /* SPARSE_H */
