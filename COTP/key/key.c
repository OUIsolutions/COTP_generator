


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
        char temporary_key[30] ={0};
        sprintf(temporary_key,"%lu",seed_in_int);
        key = private_ctop_sub_str(temporary_key,0,generated_key_size);
        free(sha_seed);
    }


    char *seed_mark = private_ctop_format_num(generated_key_size,3);
    int result_size = generated_key_size + 3;
    char *result = (char*)malloc(result_size+2);


    sprintf(result,"%s%s",seed_mark,key);
    free(key);
    free(seed_mark);

    return result;

}

