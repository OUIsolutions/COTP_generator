//
// Created by jurandi on 21-06-2023.
//
#define CTOP_DEBUG
#include "COTP/COTP_main.h"
#include "COTP/COTP_main.h"

int main(){

    const char *secreet = "akisjioajsidjioasidais";
    int interval = 10;
    CtopKeyAttributes  key_attribtes = newCtopKeyAttributes_from_time(
            interval,
            secreet,
            time(NULL)
    );

    CtopKeyAttributes_represent_key_attributes(&key_attribtes);

}