#include <stdlib.h>
#include <string.h>
#include <sparse.h>


char** SPARSE_allocated_args = NULL;
int SPARSE_initialized = 0;
int SPARSE_current_arg = 0;


__SPARSE_EXTERN_INLINE void
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


__SPARSE_EXTERN_INLINE void
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
__SPARSE_EXTERN_INLINE char*
sparse_flag(char *name, char *defaultValue, int argc, char **argv)
{
        sparse_init();

        /* generate the flag name */
        char flagName[FLAG_MAX_SIZE];
        strcpy(&flagName[0], "--");
        strcpy(&flagName[2], name);
        strcpy(&flagName[strlen(name) + 2], "=");

        /* return value */
        char *content = NULL;

        /* iterate over argv */
        int j;
        for (j = 0; j < argc; j++)
        {
                char *arg = argv[j];

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
