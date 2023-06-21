

void ctop_create_pseud_random_key(
        char *result,
        const char *secret,
        const char *seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters_on_key,
        bool allow_letters_on_password
){

    char key[65] = {0};
    int generated_key_size;
    char formated_secret[300] = {0};
    sprintf(formated_secret,"%s%d", secret, seed);
    if(allow_letters_on_key){
        char sha_seed[65] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, formated_secret, strlen(secret));

        generated_key_size = private_ctop_sanitize_range(key_size, 5 , 64);
        private_ctop_sub_str(
                key,
                sha_seed,
                0,
                generated_key_size
        );

    }
    else{
        char sha_seed[65] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, formated_secret, strlen(secret));
        unsigned long seed_in_int = private_ctop_transform_string_in_number(sha_seed);
        generated_key_size = private_ctop_sanitize_range(key_size, 5, 19);
        char temporary_key[20] ={0};
        sprintf(temporary_key,"%lu",seed_in_int);
        private_ctop_sub_str(key, temporary_key, 0, generated_key_size);

    }
    printf("key_size: %d\n", strlen(key));

    char key_mark[3] = {0};
    private_ctop_format_num(key_mark, generated_key_size, 2);


    char interval_string[12]= {0};
    sprintf(interval_string,"%d",interval);
    char interval_mark[3] = {0};
    private_ctop_format_num(interval_mark,(int)strlen(interval_string),2);

    char password_size_formated[3] = {0};
    private_ctop_format_num(
            password_size_formated,
            private_ctop_sanitize_range(password_size, 5, 64),
            2
            );

    sprintf(result, "%s%s%s%s%s%d",
            key_mark,
            key,
            interval_mark,
            interval_string,
            password_size_formated,
            (bool)allow_letters_on_password
      );

#ifdef CTOP_DEBUG
    printf("generating seed ----------------------------------------------------\n");
    printf("\tkey mark:%s\n",key_mark);
    printf("\tkey:%s\n",key);
    printf("\tinterval mark:%s\n",interval_mark);
    printf("\tinterval:%s\n",interval_string);
    printf("\tpassword size:%s\n", password_size_formated);
    printf("\tallow letters:%d\n",(bool)allow_letters_on_password);
    printf("\tseed:%s\n",result);
#endif
}

void ctop_get_passowrd(char *result,const char *keey){

    int acumulator = 0;
    char key_mark[3] = {0};
    private_ctop_sub_str(key_mark, keey, acumulator, 2);
    acumulator+=2;
    int key_size = atoi(key_mark);
    char key[64] = {0};
    private_ctop_sub_str(key, keey, acumulator, key_size + acumulator);
    acumulator+=key_size;
    char interval_mark[3] = {0};
    private_ctop_sub_str(interval_mark, keey, acumulator, acumulator + 2);
    int interval_size = atoi(interval_mark);


    #ifdef CTOP_DEBUG
        printf("generating password ----------------------------------------------------\n");
        printf("\tkey mark:%s\n",key_mark);
        printf("\tkey:%s\n",key);
        printf("\tinterval mark:%s\n",interval_mark);
    #endif


    acumulator+=key_size;

}