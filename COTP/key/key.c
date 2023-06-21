

char * ctop_create_key(
        const char *seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters
){
    char *sha_seed = calc_sha_256_from_string_returning_string(seed);
    int seed_size = private_ctop_sanitize_range(key_size, 10 , 256);
    char *formated_seed = private_ctop_sub_str(
            sha_seed,
            0,
            seed_size
    );
    free(sha_seed);
    char *seed_mark = private_ctop_format_num(seed_size,3);
    int result_size = seed_size + 3;
    char *result = (char*)malloc(result_size+2);


    sprintf(result,"%s%s",seed_mark,formated_seed);
    free(formated_seed);
    free(seed_mark);



    return result;

}

