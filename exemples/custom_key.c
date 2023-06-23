
#include "COTPgenerator.h"

int main(){
    //Not share these in any public repo
    const char *secreet = "jisduohfuhusdh8q0j023233321";
    //the interval betewen password changing
    int interval = cotp_minutes(30);
    long now = time(NULL);
    COTPKeyAttributes  key_attribtes = newCOTPKeyAttribute(
            interval,
            secreet,
            now
    );
    key_attribtes.key_size = 50;
    key_attribtes.password_size = 10;
    key_attribtes.allow_letters_on_passowrd = false;
    key_attribtes.allow_letters_on_key = false;

    char key[COTP_MAX] = {0};
    cotp_create_key_string_from_attributes(key, &key_attribtes);
    printf("save these key:\n%s\n", key);
    return 0;
}