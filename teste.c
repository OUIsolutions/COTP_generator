//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){
    printf("----------- Key Construction ----------------\n");
    const char *secreet = "akisjioajsidjioasidaisr";
    int interval = ctops_days(77000);

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

    CTopParsedKey parsed_key = ctop_parse_key(key);
    CTopParsedKey_reprsent(&parsed_key);
}