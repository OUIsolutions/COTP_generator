


void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval){
    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = 64;
    attributes->interval = interval;
    attributes->password_size = 20;
}

CtopKeyAttributes newCtopKeyAttributes_from_time(int interval, const char *secret, unsigned  long current_time){
    CtopKeyAttributes keey_attributes;
    private_ctop_initialize_key_attribtes(&keey_attributes,interval);
    char seed[100] = {0};
    sprintf(seed,"%s%ld",secret,current_time);
    strcpy(keey_attributes.seed,seed);
    return keey_attributes;
}


void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes){

    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on key_attributes: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}


/*
void ctop_create_pseud_random_key(
        char *result,
        const char *seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters_on_key,
        bool allow_letters_on_password
){

    char key_attributes[65] = {0};
    int generated_key_size;
    if(allow_letters_on_key){
        char sha_seed[65] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, seed, strlen(seed));

        generated_key_size = private_ctop_sanitize_range(key_size, 5 , 64);
        private_ctop_sub_str(
                key_attributes,
                sha_seed,
                0,
                generated_key_size
        );

    }
    else{
        char sha_seed[65] = {0};
        private_ctop_calc_sha_256_returning_string(sha_seed, seed, strlen(seed));
        unsigned long seed_in_int = private_ctop_transform_string_in_number(sha_seed);
        generated_key_size = private_ctop_sanitize_range(key_size, 5, 19);
        char temporary_key[20] ={0};
        sprintf(temporary_key,"%lu",seed_in_int);
        private_ctop_sub_str(key_attributes, temporary_key, 0, generated_key_size);

    }
    printf("key_size: %d\n", strlen(key_attributes));

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
            key_attributes,
            interval_mark,
            interval_string,
            password_size_formated,
            (bool)allow_letters_on_password
      );

#ifdef CTOP_DEBUG
    printf("generating seed ----------------------------------------------------\n");
    printf("\tkey_attributes mark:%s\n",key_mark);
    printf("\tkey_attributes:%s\n",key_attributes);
    printf("\tinterval mark:%s\n",interval_mark);
    printf("\tinterval:%s\n",interval_string);
    printf("\tpassword size:%s\n", password_size_formated);
    printf("\tallow letters:%d\n",(bool)allow_letters_on_password);
    printf("\tseed:%s\n",result);
#endif
}
/**
void ctop_get_passowrd(char *result,const char *keey){

    int acumulator = 0;
    char key_mark[3] = {0};
    private_ctop_sub_str(key_mark, keey, acumulator, 2);
    acumulator+=2;
    int key_size = atoi(key_mark);
    char key_attributes[64] = {0};
    private_ctop_sub_str(key_attributes, keey, acumulator, key_size + acumulator);
    acumulator+=key_size;
    char interval_mark[3] = {0};
    private_ctop_sub_str(interval_mark, keey, acumulator, acumulator + 2);
    int interval_size = atoi(interval_mark);


    #ifdef CTOP_DEBUG
        printf("generating password ----------------------------------------------------\n");
        printf("\tkey_attributes mark:%s\n",key_mark);
        printf("\tkey_attributes:%s\n",key_attributes);
        printf("\tinterval mark:%s\n",interval_mark);
    #endif


    acumulator+=key_size;

}
 */