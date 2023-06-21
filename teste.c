//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
int main(){

    char key[CTOP_MAX] = {0};
    const char *secret = "ijsiofushaiuhsiuahuissahuhasusaupspausuasaipus";

    ctop_create_pseud_random_key(
            key,
             secret,
            1,
            CTOP_MAX,
            ctop_minutes(600000),
            CTOP_MAX,
            true,
            true
    );

    char password[CTOP_MAX];
    ctop_get_passowrd(password,key);
}