


void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval){

    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = 81 + CTOP_DESCRIPTION_SIZE;
    attributes->interval = interval;
    attributes->password_size = 20;

}


CtopKeyAttributes newCtopKeyAttribute(int interval, const char *secret, unsigned  long current_time){
    CtopKeyAttributes keey_attributes = {0};
    private_ctop_initialize_key_attribtes(&keey_attributes,interval);
    sprintf(keey_attributes.seed,"%s%ld",secret,current_time);
    return keey_attributes;
}


CtopKeyAttributes ctop_parse_key(const char *key){
    CtopKeyAttributes keey_attributes = {0};
    keey_attributes.key_size =strlen(key);
    int sha_size  = keey_attributes.key_size - CTOP_DESCRIPTION_SIZE;

    private_ctop_sub_str(
             keey_attributes.seed,
             key,
             0,
             sha_size
    );
    return  keey_attributes;


}

void private_ctop_sanitize_attributes(CtopKeyAttributes *attributes){

    int min_key_size = 20 +CTOP_DESCRIPTION_SIZE;
    int max_key_size = 64 +CTOP_DESCRIPTION_SIZE;

    if(!attributes->allow_letters_on_key){
        max_key_size = 81 +CTOP_DESCRIPTION_SIZE;
    }
    attributes->key_size = private_ctop_sanitize_range(
            attributes->key_size,
            min_key_size,
            max_key_size
    );

    int min_password_size = 5;
    int max_password_size = 64;

    if(!attributes->allow_letters_on_passowrd){
        max_password_size = 81;
    }

    attributes->password_size = private_ctop_sanitize_range(
            attributes->password_size,
            min_password_size,
            max_password_size
    );

}


void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes){
    private_ctop_sanitize_attributes(attributes);
    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("keey size: %d\n",attributes->key_size);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on KeyAttributes: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}

void ctop_create_key(
        char *key,
        CtopKeyAttributes *attributes
){


    private_ctop_sanitize_attributes(attributes);
    //creating the elements

    char interval[11] = {0};
    private_ctop_format_num(interval,attributes->interval,10);

    char password_size[3] = {0};
    private_ctop_format_num(password_size,attributes->password_size,2);



    char sha_of_seed[82] = {0};
    char seed[82] = {0};


    if(attributes->allow_letters_on_key){

        private_ctop_calc_sha_256_generating_string(
                sha_of_seed,
                attributes->seed
        );

    }
    else{

        private_ctop_calc_sha_256_generating_number(
                sha_of_seed,
                attributes->seed
        );

    }

    private_ctop_sub_str(seed,sha_of_seed,0,attributes->key_size - CTOP_DESCRIPTION_SIZE);

    sprintf(key,
            "%s%s%s%d",
            seed,
            interval,
            password_size,
            attributes->allow_letters_on_passowrd
    );

}
