//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){
    printf("----------- Key Construction ----------------\n");
    const char *secreet = "akisjioajsidjioasidais";
    int interval = ctops_days(500);

    CtopKeyAttributes  key_attribtes = newCtopKeyAttribute(
            interval,
            secreet,
            time(NULL)
    );

    CtopKeyAttributes_represent_key_attributes(&key_attribtes);
    printf("----------- Key Generation ----------------\n");
    char key[CTOP_MAX] = {0};
    ctop_create_key(key,&key_attribtes);
    printf("key: %s\n", key);
    printf("----------- Key parsing ----------------\n");

    CtopKeyAttributes parsed = ctop_parse_key(key);
    CtopKeyAttributes_represent_key_attributes(&parsed);

}