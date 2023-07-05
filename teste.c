#include "COTPgenerator.h"


int main(){

    const char *key = "6fb07055e72bbe50e1a5f4ffe1ff787d7dcb037940a49e7dfbbea87567ff6fee00000060100";

    char password[COTP_MAX]  = {0};
    int time_remaning;

    while(true){
        system("clear");

        long now = time(NULL);
        cotp_get_password(password,&time_remaning,key,now);
        printf("password: %s\n",password);
        printf("time remaning :%d\n",time_remaning);
        sleep(1);
    }
}
//6fb07055e72bbe50e1a5f4ffe1ff787d7dcb037940a49e7dfbbea87567ff6fee00000060100