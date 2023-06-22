


void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval){

    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = 64;
    attributes->interval = interval;
    attributes->password_size = 20;

}

void private_ctop_sanitize_attributes(CtopKeyAttributes *attributes){

    int min_size = 5;
    int max_key_size = 64;
    int max_password_size = 64;

    if(!attributes->allow_letters_on_key){
        max_key_size = 19;
    }
    if(!attributes->allow_letters_on_passowrd){
        max_password_size = 19;
    }
    attributes->password_size = private_ctop_sanitize_range(
            attributes->password_size,
            min_size,
            max_password_size
    );
    attributes->key_size = private_ctop_sanitize_range(
            attributes->key_size,
            min_size,
            max_key_size
    );
}

CtopKeyAttributes newCtopKeyAttribute(int interval, const char *secret, unsigned  long current_time){

    CtopKeyAttributes keey_attributes = {0};
    private_ctop_initialize_key_attribtes(&keey_attributes,interval);
    sprintf(keey_attributes.seed,"%s%ld",secret,current_time);
    return keey_attributes;
}


void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes){
    private_ctop_sanitize_attributes(attributes);
    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("keey size: %d\n",attributes->key_size);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on key_attributes: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}
void ctop_create_key(
        char *result,
        CtopKeyAttributes *attributes
){


    private_ctop_sanitize_attributes(attributes);
    //creating the elements

    char interval[10] = {0};
    private_ctop_format_num(interval,attributes->interval,10);

    char password_size[3] = {0};
    private_ctop_format_num(password_size,attributes->password_size,2);



    char sha_of_seed[65] = {0};
    char seed[65] = {0};

    if(attributes->allow_letters_on_key){
        private_ctop_calc_sha_256_generating_string(
                sha_of_seed,
                attributes->seed,
                strlen(attributes->seed)
        );
    }
    else{
        private_ctop_calc_sha_256_generating_number(
                sha_of_seed,
                attributes->seed,
                strlen(attributes->seed)
        );
    }
    private_ctop_sub_str(seed,sha_of_seed,0,attributes->key_size);

    sprintf(result,"%s%s%d%s",
            interval,
            password_size,
            attributes->allow_letters_on_passowrd,
            seed
    );

}
