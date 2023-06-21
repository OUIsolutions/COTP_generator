


char * ctop_create_key(
        const char *seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters_on_key,
        bool allow_letters_on_password
){

    char * key;
    int generated_key_size;

    if(allow_letters_on_key){
        char *sha_seed = calc_sha_256_from_string_returning_string(seed);
        generated_key_size = private_ctop_sanitize_range(key_size, 5 , 256);
        key = private_ctop_sub_str(
                sha_seed,
                0,
                generated_key_size
        );
        free(sha_seed);
    }
    else{
        char *sha_seed = calc_sha_256_from_string_returning_string(seed);
        unsigned long seed_in_int = private_ctop_transform_string_in_number(sha_seed);
        generated_key_size = private_ctop_sanitize_range(key_size,5,19);
        char temporary_key[20] ={0};
        sprintf(temporary_key,"%lu",seed_in_int);
        key = private_ctop_sub_str(temporary_key,0,generated_key_size);
        free(sha_seed);
    }

    char *seed_mark = private_ctop_format_num(generated_key_size,3);

    char interval_string[12]= {0};
    sprintf(interval_string,"%d",interval);
    char *interval_mark  = private_ctop_format_num((int)strlen(interval_string),2);


    char result[400];

    #ifdef CTOP_DEBUG
        sprintf(result,"%s|%s|%s|%s",seed_mark,key,interval_mark,interval_string);
    #else
        sprintf(result,"%s%s%s%s",seed_mark,key,interval_mark,interval_string);
    #endif

    free(key);
    free(seed_mark);
    free(interval_mark);
    return strdup(result);

}

