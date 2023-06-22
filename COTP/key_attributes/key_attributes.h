


#define CTOP_MAX 100

#define CTOP_DESCRIPTION_SIZE 13


typedef struct CtopKeyAttributes{
    char seed[200];
    int interval;
    int password_size;
    int key_size;
    bool allow_letters_on_passowrd;

    bool allow_letters_on_key;
}CtopKeyAttributes;

void private_ctop_initialize_key_attribtes(CtopKeyAttributes *attributes,int interval);


CtopKeyAttributes newCtopKeyAttribute(int interval, const char *secret, unsigned  long current_time);

CtopKeyAttributes ctop_parse_key(const char *key);

void private_ctop_sanitize_attributes(CtopKeyAttributes *attributes);

void CtopKeyAttributes_represent_key_attributes(CtopKeyAttributes *attributes);


void ctop_create_key(
        char *key,
        CtopKeyAttributes *attributes
);


