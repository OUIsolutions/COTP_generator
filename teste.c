//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"


int main(){
    printf("----------- Key Construction ----------------\n");

    const char *secreet = "akisjioajsidjioasidaisr";
    int interval = ctop_minutes(30);

    CtopKeyAttributes  key_attribtes = newCtopKeyAttribute(
            interval,
            secreet,
            time(NULL)
    );
    key_attribtes.allow_letters_on_key = false;
    key_attribtes.allow_letters_on_passowrd = false;
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
    int now = 1;
    int duration = 3;
    int last_point  = (int)(now / duration) * duration;
    int next_point = last_point + duration;
    int remaning = next_point - now;
    printf("last point :%i\n",last_point);
    printf("next point :%i\n",next_point);
    printf("remaning   :%i\n",remaning);


}