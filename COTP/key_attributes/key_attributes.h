


#define CTOP_MAX 100


typedef struct CtopKeyAttributes{
    char seed[200];
    int interval;
    int password_size;
    int key_size;
    bool allow_letters_on_passowrd;

    bool allow_letters_on_key;
}CtopKeyAttributes;

void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval);


void private_ctop_sanitize_attributes(CtopKeyAttributes *attributes);

CtopKeyAttributes newCtopKeyAttribute(int interval, const char *secret, unsigned  long current_time);


void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes);


void ctop_create_key(
        char *result,
        CtopKeyAttributes *attributes
);


