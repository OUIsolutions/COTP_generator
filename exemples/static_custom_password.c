//
// Created by jurandi on 23-06-2023.
//
//
// Created by jurandi on 23-06-2023.
//

// Created by jurandi on 23-06-2023.
//

#include "COTPgenerator.h"


int main(){

    const char *key = "14817323945224231901655816816168160141200001800100";

    char password[COTP_MAX]  = {0};
    long now = 1;
    int time_remaning;
    cotp_get_password(
            password,
            &time_remaning,
            key,
            now
    );
    printf("key: %s\n",password);
    printf("time remaning: %d\n",time_remaning);
}
