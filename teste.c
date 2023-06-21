//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
int main(){
     char seed[400] = {0};

    ctop_create_ctop_seed(
            seed,
            "432",
            CTOP_MAX,
            ctop_minutes(1),
            CTOP_MAX,
            true,
            true
    );

     char password[CTOP_MAX];
    ctop_get_passowrd(password,seed);
}