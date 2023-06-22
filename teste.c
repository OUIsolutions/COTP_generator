//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){

    const char *secreet = "akisjioajsidjioasidais";
    int interval = ctops_days(500);
    CtopKeyAttributes  key_attribtes = newCtopKeyAttribute(
            interval,
            secreet,
            time(NULL)
    );
    key_attribtes.password_size = 3000;
    key_attribtes.allow_letters_on_key = false;
    //CtopKeyAttributes_represent_key_attributes(&key_attribtes);

    char key[300] = {0};
;
    private_ctop_calc_sha_256_generating_number(key,"aaaaa");

    printf("\nnumber key  %d\n", strlen(key));
    char key2[300] = {0};

    private_ctop_calc_sha_256_generating_string(key2,"aaaaa");
    printf("\nstring key %s\n",key2);

}