


#define CTOP_MAX 100


typedef struct CtopKeyAttributes{
    char seed[100];
    int interval;
    int key_size;
    int password_size;
    bool allow_letters_on_key;
    bool allow_letters_on_passowrd;
}CtopKeyAttributes;

void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval);


CtopKeyAttributes newCtopKeyAttributes_from_long(int interval, const char *secret, unsigned  long current_time);

CtopKeyAttributes newCtopKeyAttributes_from_string(int interval,const char *secret, const char *second_secret);



void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes);


void ctop_create_pseud_random_key(
        char *result,
        CtopKeyAttributes *attributes
);





//void ctop_get_passowrd(char *result,const char *keey);
