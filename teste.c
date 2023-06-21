//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
int main(){

    const char *secret = "ijsiofushaiuhsiuahuissahuhasusaupspausuasaipus";


    char seed[200] ={0};
    ctop_create_pseudo_random_seed(seed,secret, 1);
    char key[CTOP_MAX] = {0};
    ctop_create_pseud_random_key(
            key,
            seed,
            CTOP_MAX,
            ctop_minutes(600000),
            CTOP_MAX,
            true,
            true
    );

    char password[CTOP_MAX];
    ctop_get_passowrd(password,key);
}