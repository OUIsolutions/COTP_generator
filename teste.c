//
// Created by jurandi on 21-06-2023.
//
#include "COTP/COTP_main.h"
int main(){

    char *key = ctop_create_key("dssdds",1000, ctop_minutes(1),4,true);
    printf("%s\n",key);

}