


void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval){
    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = 64;
    attributes->interval = interval;
    attributes->password_size = 20;
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

