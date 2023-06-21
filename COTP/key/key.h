


#define CTOP_MAX 100
#define CTOP_ALLOW_LETTERS true
#define CTOP_ONLY_NUMBERS false

void ctop_create_seed_from_long(char *result, const char *secret, unsigned  long current_time);
void ctop_create_seed_from_string(char *result, const char *secret, const char *second_secret);

void ctop_create_pseud_random_key(
        char *result,
        const char *seed,
        int key_size,
        int interval,
        int password_size,
        bool allow_letters_on_key,
        bool allow_letters_on_password
);



void ctop_get_passowrd(char *result,const char *keey);
