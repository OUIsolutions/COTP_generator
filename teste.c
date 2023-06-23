#include "COTPgenerator.h"


int main(){

    const char *key = "b66458015370cd0eb641ed89a9159d9cb3f304e019dc4323065fe7bc067c353500000060201";

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