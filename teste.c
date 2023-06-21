//
// Created by jurandi on 21-06-2023.
//
#include "COTP/COTP_main.h"
int main(){

    char *r = ctop_create_key("iasiaisai", ctops_days(10000),10,true,false);
    printf("generated_ key:%s\n",r);
}