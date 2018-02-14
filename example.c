#include "sparse.h"
#include "stdio.h"

int
main(int argc, char const *argv[])
{
        char *f1 = sparse_flag("flag1", "FALSE", argc, argv);
        char *f2 = sparse_flag("flag2", "defaultval", argc, argv);
        char *f3 = sparse_flag("flag3", "bye", argc, argv);
        char *f4 = sparse_flag("flag4", "Bye world", argc, argv);
        char *f5 = sparse_flag("flag5", "default", argc, argv);
        char *f6 = sparse_flag("flag5", "FALSE", argc, argv);

        printf("f1 = %s\n", f1);
        printf("f2 = %s\n", f2);
        printf("f3 = %s\n", f3);
        printf("f4 = %s\n", f4);
        printf("f5 = %s\n", f5);

        return 0;

}
