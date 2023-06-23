//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){
    printf("----------- Key Construction ----------------\n");

    const char *secreet = "akisjioajsidjioasidaisr";
    int interval = cotp_minutes(1);

    COTPKeyAttributes  key_attribtes = newCtopKeyAttribute(
            interval,
            secreet,
    1
    );


    CtopKeyAttributes_represent_key_attributes(&key_attribtes);

    printf("----------- Key Generation ----------------\n");
    char key[CTOP_MAX] = {0};
    cotp_create_key(key, &key_attribtes);
    printf("key: %s\n", key);
    printf("----------- Key parsing ----------------\n");

    COTParsedKey parsed_key = cotp_parse_key(key);
    COTPParsedKey_reprsent(&parsed_key);

    printf("----------- Getting password ----------------\n");
    char password[CTOP_MAX] = {0};
    int remaning;
    cotp_get_password(password, &remaning, key, time(NULL));
    printf("password: %s\n",password);
    printf("remaning: %d\n",remaning);

}