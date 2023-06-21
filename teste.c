//
// Created by jurandi on 21-06-2023.
//
#include "COTP/COTP_main.h"
int main(){

    char *key = ctop_create_key(
            "dssdds3sdsfs",
            19,
            ctop_minutes(1),
            4,
            false,
            true
    );

    printf("%s\n",key);

}