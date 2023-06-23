
CTopParsedKey ctop_parse_key(const char *key){

    CTopParsedKey parsed_key = {0};
    int key_size = (int)strlen(key);
    int sha_point = key_size - CTOP_DESCRIPTION_SIZE;

    private_ctop_sub_str(
            parsed_key.generated_sha,
            key,
            0,
            sha_point
    );
    int interval_point = sha_point+8;
    parsed_key.interval = private_ctop_int_sub_str(key,sha_point,interval_point);
    int password_point = interval_point+2;
    parsed_key.password_size =  private_ctop_int_sub_str(key,interval_point,password_point);

    parsed_key.allow_letters_on_passowrd = false;

    if(key[key_size-1] == '1'){
        parsed_key.allow_letters_on_passowrd = true;
    }



    return parsed_key;

}

void CTopParsedKey_reprsent(CTopParsedKey *parsed_key){
    printf("generated sha: %s\n",parsed_key->generated_sha);
    printf("interval: %d\n",parsed_key->interval);
    printf("password size: %d\n",parsed_key->password_size);
    printf("allow letters on password: %s\n",parsed_key->allow_letters_on_passowrd? "true":"false");
}
void CTopParsedKey_get_password(CTopParsedKey *parsed_key,char *password,int *time_ramaing,long actual_time){

}

void ctop_get_password(char *password,int *time_ramaing,const char *key,long actual_time){
    CTopParsedKey parsed_key = ctop_parse_key(key);
    CTopParsedKey_get_password(&parsed_key,password,time_ramaing,actual_time);
}
