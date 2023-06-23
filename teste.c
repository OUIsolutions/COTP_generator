//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){
    printf("----------- Key Construction ----------------\n");

    const char *secreet = "akisjioajsidjioasidaisr";
    int interval = ctop_minutes(1);

    CtopKeyAttributes  key_attribtes = newCtopKeyAttribute(
            interval,
            secreet,
    1
    );
    CtopKeyAttributes_represent_key_attributes(&key_attribtes);

    printf("----------- Key Generation ----------------\n");
    char key[CTOP_MAX] = {0};
    ctop_create_key(key,&key_attribtes);
    printf("key: %s\n", key);
    printf("----------- Key parsing ----------------\n");

    CTopParsedKey parsed_key = ctop_parse_key(key);
    CTopParsedKey_reprsent(&parsed_key);
    printf("----------- Getting password ----------------\n");

    char password[CTOP_MAX] = {0};
    int remaning;
    ctop_get_password(password,&remaning,key,time(NULL));

    printf("password: %s\n",password);
    printf("remaning: %d\n",remaning);

}