//
// Created by jurandi on 21-06-2023.
//
#include "COTP/COTP_main.h"
int main(){
     char result[400] = {0};

     ctop_create_key(
             result,
            "432",
            400,
            ctops_days(500000),
             400,
            false,
            false
    );

     printf("%s\n",result);

}