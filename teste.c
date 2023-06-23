
#include "COTPgenerator.h"


int main(){

    const char *key = "2fa4bb1ad83d3aacd2f5e645c0e6289b65bd5e84a7d0d623dd549f9ef7b691a300001800201";

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