# simple-parse

Mac OS ![](https://cloud.githubusercontent.com/assets/1885333/17059766/2530c9d8-4ffd-11e6-9529-3fa47dbff616.png) and ![](https://cloud.githubusercontent.com/assets/1885333/17059750/11c4474e-4ffd-11e6-89e1-2486ca5b3234.png) | ![](https://cloud.githubusercontent.com/assets/1885333/17059763/206a7d4a-4ffd-11e6-859e-7856902fb300.png)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Travis CI: [![Build Status](https://travis-ci.org/ulises-jeremias/simple-parse.svg?branch=master)](https://travis-ci.org/ulises-jeremias/simple-parse)                                                                        | [AppVeyor: [![Build status](https://ci.appveyor.com/api/projects/status/mpc8xk0odl5er0lk/branch/master?svg=true)](https://ci.appveyor.com/project/ulises-jeremias/simple-parse/branch/master)

Simple, stupid and portable C argument (argv) parser. SParse is inspired by [cargo](https://github.com/funlibs/cargo). The idea is to expand the functionalities that this library offers, reimplement them and add new ones.

## Build

Just include sparse.h to your project.

SParse tests are built with CMake for all platforms. You can also use the fake configure script provided to set it up on unix:

```sh
$ ./configure
$ make
```

## Example

To handle the following program arguments:

```sh
./myprog --flag1 --flag2= --flag3=hello --flag4="Hello world"
```

You could write this:

```c
#include <stdlib.h>
#include <sparse.h>

int main(int argc, char* argv[])
{
    char *f1 = sparse_flag("flag1", "FALSE", argc, argv);         /* f1 = "TRUE" */
    char *f2 = sparse_flag("flag2", "defaultval", argc, argv);    /* f2 = "" */
    char *f3 = sparse_flag("flag3", "bye", argc, argv);           /* f3 = "hello" */
    char *f4 = sparse_flag("flag4", "Bye world", argc, argv);     /* f4 = "Hello world" */
    char *f5 = sparse_flag("flag5", "default", argc, argv);       /* f5 = "default" */
    char *f6 = sparse_flag("flag6", "FALSE", argc, argv);         /* f6 = "FALSE" */

    return 0;
}
```
