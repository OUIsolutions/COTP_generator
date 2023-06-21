//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
int main(){
     char seed[CTOP_MAX] = {0};
    ctop_create_ctop_seed(
            seed,
            "a",
            CTOP_MAX,
            ctop_minutes(600000),
            CTOP_MAX,
            true,
            true
    );

     char password[CTOP_MAX];
    ctop_get_passowrd(password,seed);
}