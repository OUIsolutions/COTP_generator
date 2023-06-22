


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
            max_password_size
    );
}

CtopKeyAttributes newCtopKeyAttributes_from_time(int interval, const char *secret, unsigned  long current_time){
    CtopKeyAttributes keey_attributes = {0};
    private_ctop_initialize_key_attribtes(&keey_attributes,interval);
    sprintf(keey_attributes.seed,"%s%ld",secret,current_time);
    return keey_attributes;
}


void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes){

    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("keey size: %d\n",attributes->key_size);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on key_attributes: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}

