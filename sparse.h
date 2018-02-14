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
#endif /* __cplusplus */

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

        if (SPARSE_current_arg == 0)
        {
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

/**
 * @brief Get the content of a flag if it is an assignment flag (--myflag=),
 * the string "TRUE" if the flag is defined as boolean (--myflag)
 * or the default value if neither assignment or boolean flag is defined.
 *
 * If the flag is defined multiple time, as boolean or assignment, the value of
 * the last flag occurence is returned.
 *
 * @param flag The flag name
 *
 * @param defaultValue The default value if the flag is not found
 *
 * @param argc The original main(argc,_) value
 *
 * @param argv The original main(_,argv) value
 *
 * @return A pointer to a char array. It is up to the user to free() this array.
 */
static char*
sparse_flag(char* name, char* defaultValue, int argc, char **argv)
{
        sparse_init();

        /* generate the flag name */
        char flagName[FLAG_MAX_SIZE];
        strcpy(&flagName[0], "--");
        strcpy(&flagName[2], name);
        strcpy(&flagName[strlen(name) + 2], "=");

        /* return value */
        char* content = NULL;

        /* iterate over argv */
        int j;
        for (j = 0; j < argc; j++)
        {
                char* arg = argv[j];

                if (strncmp(flagName, arg, strlen(flagName)) == 0)
                {
                        /* flag found with "=" */

                        if (strlen(flagName) == strlen(arg))
                        { /* no content */
                                if (content != NULL) free(content);
                                content = (char*) malloc(1);
                                *content = '\0';

                                continue;
                        }

                        /* there is some content */
                        if (content != NULL)
                                free(content);

                        content = (char*) malloc(strlen(arg) - strlen(flagName) + 1);
                        strcpy(content, &arg[strlen(flagName)]);

                }
                else if (strncmp(flagName, arg, strlen(flagName) - 1) == 0)
                {
                        /* found partial flag --${name}
                           set content to true if it is the end of the str */
                        if (strlen(arg) == strlen(flagName) - 1)
                        {
                                if (content != NULL)
                                        free(content);
                                content = (char*) malloc(strlen("TRUE") + 1);
                                strcpy(content, "TRUE");
                        }
                }
        }

        if (content == NULL)
        { /* flag not found set default or null */
                if (defaultValue == NULL)
                {
                        content = NULL;
                }
                else
                {
                        content = (char*) malloc(strlen(defaultValue) + 1);
                        strcpy(content, defaultValue);
                }
        }

        SPARSE_allocated_args[SPARSE_current_arg] = content;
        SPARSE_current_arg += 1;

        return content;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPARSE_H */
