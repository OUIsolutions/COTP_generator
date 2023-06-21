//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
int main(){

    char *key = ctop_create_key(
            "dssdds3sdsfs",
            5,
            ctops_days(500000),
            4,
            true,
            true
    );

    printf("%s\n",key);

}