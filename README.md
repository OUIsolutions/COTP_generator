# COTP_generator
COTP Generator its an single header C/C++ lib to generate 
One Time Passwords, its totaly memory safe and easy to use


# Installation

The installation of COTP_generator is made to be as dumb as possible, 
just  download the file  amalgamation **COTPgenerator.h**  and include in your project.
if this compiles then the library will work:

~~~c
#include "COTPgenerator.h"

int main(int argc, char *argv[]){


    return 0;
}
~~~

## Full Folder
Alternatively you can download the entire **COTP** folder and include the **COTP/COTP_main.h** file
~~~c

#include "COTP/COTP_main.h"

int main(int argc, char *argv[]){


return 0;
}
~~~


## sha-256 <br>
**sha-256**: from https://github.com/amosnier/sha-2 <br>

Zero Clause BSD License
© 2021 Alain Mosnier

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
