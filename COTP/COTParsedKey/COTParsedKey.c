
COTParsedKey cotp_parse_key(const char *key){

    COTParsedKey parsed_key = {0};
    int key_size = (int)strlen(key);
    int sha_point = key_size - COTP_DESCRIPTION_SIZE;

    private_cotp_sub_str(
            parsed_key.generated_sha,
            key,
            0,
            sha_point
    );
    int interval_point = sha_point+8;
    parsed_key.interval = private_cotp_int_sub_str(key, sha_point, interval_point);
    int password_point = interval_point+2;
    parsed_key.password_size = private_cotp_int_sub_str(key, interval_point, password_point);

    parsed_key.allow_letters_on_passowrd = false;

    if(key[key_size-1] == '1'){
        parsed_key.allow_letters_on_passowrd = true;
    }



    return parsed_key;

}

void COTPParsedKey_reprsent(COTParsedKey *parsed_key){
    printf("generated sha: %s\n",parsed_key->generated_sha);
    printf("interval: %d\n",parsed_key->interval);
    printf("password size: %d\n",parsed_key->password_size);
    printf("allow letters on password: %s\n",parsed_key->allow_letters_on_passowrd? "true":"false");
}


void COTPParsedKey_get_password(COTParsedKey *parsed_key, char *password, int *time_ramaing, long actual_time){

    long last_point = (long)(actual_time / parsed_key->interval) * parsed_key->interval;
    long next_point = last_point + parsed_key->interval;
    *time_ramaing = (int)(next_point - actual_time);

    char generated_sha[82] = {0};
    char generated_seed[100] = {0};
    sprintf(generated_seed,"%s%li",parsed_key->generated_sha,last_point);


    if(parsed_key->allow_letters_on_passowrd){

        private_cotp_calc_sha_256_generating_string(generated_sha, generated_seed);

    }
    else{
        private_cotp_calc_sha_256_generating_number(generated_sha, generated_seed);
    }
    private_cotp_sub_str(password, generated_sha, 0, parsed_key->password_size);
}


void cotp_get_password(char *password, int *time_ramaing, const char *key, long actual_time){
    COTParsedKey parsed_key = cotp_parse_key(key);
    COTPParsedKey_get_password(&parsed_key, password, time_ramaing, actual_time);
}