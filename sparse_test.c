#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sparse.h>


#define mu_assert(message, test) do { \
                if (!(test)) return message; \
} while (0)

#define mu_run_test(test) do { \
                char *message = test(); \
                tests_run++; \
                if (message) return message; \
} while (0)

int tests_run = 0;

static char* TEST_VALUE;
static char* TEST_EXPECTED;

static char*
sparse_compare()
{
        printf("Compare %s to %s\n", TEST_VALUE, TEST_EXPECTED);

        int diff = strcmp(TEST_VALUE, TEST_EXPECTED);
        mu_assert("Compare does not match", diff == 0);

        return NULL;
}

static char*
sparse_test(int argc, char** argv)
{

        char* testType  = sparse_flag("type", "UNDEFINED", argc, argv);
        TEST_VALUE = sparse_flag("val", "UNDEFINED", argc, argv);
        printf("type is %s %d\n", testType, strcmp(testType, "boolean"));

        if (strcmp(testType, "boolean") == 0)
        {
                TEST_EXPECTED = "TRUE";
        }
        else if (strcmp(testType, "empty") == 0)
        {
                TEST_EXPECTED = "";
        }
        else if (strcmp(testType, "value") == 0)
        {
                TEST_EXPECTED = "innerValue";
        }
        else if (strcmp(testType, "missing") == 0)
        {
                TEST_EXPECTED = "UNDEFINED";
        }
        else
        {
                return "no such test";
        }

        mu_run_test(sparse_compare);

        return NULL;

}

int
main(int argc, char* argv[])
{
        char* result = sparse_test(argc, argv);

        if (result != 0)
                printf("%s\n", result);

        return result != NULL;

}
