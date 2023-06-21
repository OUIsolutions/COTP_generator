

void ctop_create_ctop_seed(
        char *result,
        const char *raw_seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters_on_key,
        bool allow_letters_on_password
){

    char keey[257] = {0};
    int generated_key_size;

    if(allow_letters_on_key){
        char sha_seed[257] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, raw_seed, strlen(raw_seed));

        generated_key_size = private_ctop_sanitize_range(key_size, 5 , 256);
        private_ctop_sub_str(
                keey,
                sha_seed,
                0,
                generated_key_size
        );

    }
    else{
        char sha_seed[257] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, raw_seed, strlen(raw_seed));
        unsigned long seed_in_int = private_ctop_transform_string_in_number(sha_seed);
        generated_key_size = private_ctop_sanitize_range(key_size, 5, 19);
        char temporary_key[20] ={0};
        sprintf(temporary_key,"%lu",seed_in_int);
        private_ctop_sub_str(keey,temporary_key,0,generated_key_size);

    }
    char seed_mark[4] = {0};
    private_ctop_format_num(seed_mark,generated_key_size,3);

    char interval_string[12]= {0};
    sprintf(interval_string,"%d",interval);
    char interval_mark[3] = {0};
    private_ctop_format_num(interval_mark,(int)strlen(interval_string),2);

    char password_formated[4] = {0};
    private_ctop_format_num(
            password_formated,
            private_ctop_sanitize_range(password_size, 5, 256),
            3
            );


    #ifdef CTOP_DEBUG
        sprintf(result,"%s|%s|%s|%s|%s|%d",
                seed_mark,keey,interval_mark,interval_string,password_formated,(bool)allow_letters_on_password);
    #else
        sprintf(result,"%s%s%s%s%s%d",
                seed_mark,keey,interval_mark,interval_string,password_formated,(bool)allow_letters_on_password);
    #endif


}
