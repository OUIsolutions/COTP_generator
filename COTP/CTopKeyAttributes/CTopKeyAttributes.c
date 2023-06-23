


void private_cotp_initialize_key_attribtes(COTPKeyAttributes *attributes, int interval){

    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = COTP_MAX;
    attributes->interval = interval;
    attributes->password_size = 20;

}


COTPKeyAttributes newCOTPKeyAttribute(int interval, const char *secret, unsigned  long current_time){
    COTPKeyAttributes keey_attributes = {0};
    private_cotp_initialize_key_attribtes(&keey_attributes, interval);
    sprintf(keey_attributes.seed,"%s%ld",secret,current_time);
    return keey_attributes;
}



void private_cotp_sanitize_attributes(COTPKeyAttributes *attributes){

    int min_key_size = 20 + COTP_DESCRIPTION_SIZE;
    int max_key_size = 64 + COTP_DESCRIPTION_SIZE;

    if(!attributes->allow_letters_on_key){
        max_key_size = 81 + COTP_DESCRIPTION_SIZE;
    }
    attributes->key_size = private_cotp_sanitize_range(
            attributes->key_size,
            min_key_size,
            max_key_size
    );

    int min_password_size = 5;
    int max_password_size = 64;

    if(!attributes->allow_letters_on_passowrd){
        max_password_size = 81;
    }

    attributes->password_size = private_cotp_sanitize_range(
            attributes->password_size,
            min_password_size,
            max_password_size
    );

}


void COTPKeyAttributes_represent_key_attributes(COTPKeyAttributes *attributes){
    private_cotp_sanitize_attributes(attributes);
    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("keey size: %d\n",attributes->key_size);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on  key: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}

void cotp_create_key_string_from_attributes(
        char *key,
        COTPKeyAttributes *attributes
){
    private_cotp_sanitize_attributes(attributes);
    //creating the elements

    COTPKey key_object = {0};

    key_object.interval = attributes->interval;
    key_object.password_size = attributes->password_size;
    key_object.allow_letters_on_passowrd = attributes->allow_letters_on_passowrd;
    char sha_of_seed[82] = {0};
    if(attributes->allow_letters_on_key){
        private_cotp_calc_sha_256_generating_string(
                sha_of_seed,
                attributes->seed
        );

    }
    else{

        private_cotp_calc_sha_256_generating_number(
                sha_of_seed,
                attributes->seed
        );

    }
    private_cotp_sub_str(key_object.generated_sha, sha_of_seed, 0, attributes->key_size - COTP_DESCRIPTION_SIZE);

    COTPKey_object_create_key_string(key,&key_object);

}
