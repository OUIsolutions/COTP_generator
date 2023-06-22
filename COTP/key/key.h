


#define CTOP_MAX 100


typedef struct CtopKeyAttributes{
    char seed[100];
    int interval;
    int password_size;
    bool allow_letters_on_key;
    bool allow_letters_on_passowrd;
}CtopKeyAttributes;


void ctop_create_seed_from_long(CtopKeyAttributes *attributes, const char *secret, unsigned  long current_time);

void ctop_create_seed_from_string(CtopKeyAttributes *attributes, const char *secret, const char *second_secret);


void ctop_create_represent_seed(CtopKeyAttributes *attributes);


void ctop_create_pseud_random_key(
        char *result,
        CtopKeyAttributes *attributes
);





//void ctop_get_passowrd(char *result,const char *keey);
