//
// Created by jurandi on 21-06-2023.
//
#include "COTP/COTP_main.h"

int main(){

    const char *key = "a47628a2d47c54d32e14ccad1e4bcb32e99ea824a57cf0f30781773ce9a4944f00000060201";

    char password[COTP_MAX]  = {0};
    int time_remaning;

    while(true){
        system("clear");

        long now = time(NULL);
        COTPKey  key_object = cotp_parse_key(key);
        COTPKey_get_password(&key_object,password,&time_remaning,now);
        printf("password: %s\n",password);
        printf("time remaning :%d\n",time_remaning);
        sleep(1);
    }
}