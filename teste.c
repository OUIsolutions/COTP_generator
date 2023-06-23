
#include "COTPgenerator.h"

int main(){

    //Not share these in any public repo
    const char *secreet = "jisduohfuhusdh8q0j023233321";
    //the interval betewen password changing
    int interval = cotp_minutes(1);
    long now = 1;
    COTPKeyAttributes  key_attribtes = newCOTPKeyAttribute(
            interval,
            secreet,
            now
    );
    char key[COTP_MAX] = {0};
    cotp_create_key_string_from_attributes(key, &key_attribtes);
    printf("%s\n", key);
    return 0;
}