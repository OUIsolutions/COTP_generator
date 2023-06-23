


#define CTOP_MAX 100

#define CTOP_DESCRIPTION_SIZE 11


typedef struct COTPKeyAttributes{
    char seed[200];
    int interval;
    int password_size;
    int key_size;
    bool allow_letters_on_passowrd;

    bool allow_letters_on_key;
}COTPKeyAttributes;

void private_ctop_initialize_key_attribtes(COTPKeyAttributes *attributes, int interval);


COTPKeyAttributes newCtopKeyAttribute(int interval, const char *secret, unsigned  long current_time);


void private_cotp_sanitize_attributes(COTPKeyAttributes *attributes);


void CtopKeyAttributes_represent_key_attributes(COTPKeyAttributes *attributes);

void cotp_create_key(
        char *key,
        COTPKeyAttributes *attributes
);


