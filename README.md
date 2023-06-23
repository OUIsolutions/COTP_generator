# COTP_Generator
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
### Creating an Key String
all passwords are generated based on an key string + current time, for generating an key string run the following code 
the follwoing code will create an one minute changing key 

<!--codeof:exemples/random_key_generation.c-->
~~~c
//
// Created by jurandi on 21-06-2023.
//
#include "COTPgenerator.h"

int main(){

    //Not share these in any public repo
    const char *secreet = "jisduohfuhusdh8q0j023233321";
    //the interval betewen password changing
    int interval = cotp_minutes(1);
    long now = time(NULL);
    COTPKeyAttributes  key_attribtes = newCOTPKeyAttribute(
            interval,
            secreet,
            now
    );
    char key[COTP_MAX] = {0};
    cotp_create_key_string_from_attributes(key, &key_attribtes);
    printf("save these key:\n%s\n", key);
    return 0;

}
~~~

### Generating a password of key 
these code will generate the password of an key
<!--codeof:exemples/password_generation.c-->
~~~c
//
// Created by jurandi on 23-06-2023.
//

#include "COTPgenerator.h"


int main(){

    const char *key = "b66458015370cd0eb641ed89a9159d9cb3f304e019dc4323065fe7bc067c353500000060201";

    char password[COTP_MAX]  = {0};
    int time_remaning;

    while(true){
        system("clear");

        long now = time(NULL);
        cotp_get_password(password,&time_remaning,key,now);
        printf("password: %s\n",password);
        printf("time remaning :%d\n",time_remaning);
        sleep(1);
    }
}
~~~


### Creating an Custm Key
You can create custom keys with the rules you want by editing the **COTPKeyAttributes** Values 
<!--codeof:exemples/custom_key.c-->
~~~c

#include "COTPgenerator.h"

int main(){
    //Not share these in any public repo
    const char *secreet = "jisduohfuhusdh8q0j023233321";
    //the interval betewen password changing
    int interval = cotp_minutes(30);
    long now = time(NULL);
    COTPKeyAttributes  key_attribtes = newCOTPKeyAttribute(
            interval,
            secreet,
            now
    );

    //determines the size of the key
    key_attribtes.key_size = 50;
    //determines the size of the password
    key_attribtes.password_size = 10;
    //determines if the password will have latters
    key_attribtes.allow_letters_on_passowrd = false;
    //determines if the key will have letters
    key_attribtes.allow_letters_on_key = false;

    char key[COTP_MAX] = {0};
    cotp_create_key_string_from_attributes(key, &key_attribtes);
    printf("save these key:\n%s\n", key);
    return 0;
}
~~~




## sha-256 <br>
**sha-256**: from https://github.com/amosnier/sha-2 <br>

Zero Clause BSD License
© 2021 Alain Mosnier

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.