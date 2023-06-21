

char * ctop_create_key(
        const char *password,
        long interval,
        int key_size,
        bool allow_letters,
        bool encrypt_password
){

    char *key = (char*) malloc(300);

    char *created_seed = (char*)password;

    if(encrypt_password){
        created_seed = calc_sha_256_from_string_returning_string(password);
    }


}