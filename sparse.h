/**
 * @mainpage
 *
 * <a target="_blank" href="https://github.com/ulises-jeremias/simple-parse.git">See SPARSE on GitHub</a>.
 *
 * @section Usage
 * See the documentation for the sparse_flag() function.
 *
 * @section Example
 * To handle the following program arguments:
 * @code
 * ./myprog --flag1 --flag3= --flag4="Hello world"
 * @endcode
 *
 * You could write this:
 * @code
 *
 * [...]
 *
 * int main(int argc, char* argv[])
 * {
 *
 *     char* f1 = sparse_flag("flag1", "FALSE",      argc, argv); // f1 = "TRUE"
 *     char* f2 = sparse_flag("flag2", "FALSE",      argc, argv); // f2 = "FALSE"
 *     char* f3 = sparse_flag("flag3", "defaultval", argc, argv); // f3 = ""
 *     char* f4 = sparse_flag("flag4", "Bye world",  argc, argv); // f4 = "Hello world"
 *     char* f5 = sparse_flag("flag5", "Bye world",  argc, argv); // f5 = "Bye world"
 *     char* f5 = sparse_flag("flag5", NULL,  argc, argv); // f5 = NULL
 *
 * }
 * @endcode
 */

/**
 * @file sparse.h
 */
#ifndef SPARSE_H
#define SPARSE_H

#include <string.h>
#include <stdlib.h>

#define FLAG_MAX_SIZE 80
#define FLAG_MAX_NUMBER 20

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static char** SPARSE_allocated_args;
static int SPARSE_initialized = 0;
static int SPARSE_current_arg;

static void
sparse_cleanup()
{
        if (SPARSE_initialized == 0)
        {
                return;
        }

        if (SPARSE_current_arg == 0) {
                return;
        }

        int i;
        for (i = 0; i < SPARSE_current_arg; i++)
        {
                free(SPARSE_allocated_args[i]);
        }

        free(SPARSE_allocated_args);
}

static void
sparse_init()
{
        if (SPARSE_initialized == 1)
        {
                return;
        }

        SPARSE_allocated_args = (char**) malloc(sizeof (char*) * FLAG_MAX_NUMBER);
        SPARSE_current_arg = 0;
        atexit(&sparse_cleanup);
        SPARSE_initialized = 1;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SPARSE_H
