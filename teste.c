//
// Created by jurandi on 23-06-2023.
//

#include "COTP/COTP_main.h"


int main(){

    const char *key = "93872169427172161923161239171771822141200001800100";

    char password[COTP_MAX]  = {0};
    int time_remaning;


    long now = 1;
    cotp_get_password(password,&time_remaning,key,now);
    printf("password: %s\n",password);
    printf("time remaning :%d\n",time_remaning);
    sleep(1);

}