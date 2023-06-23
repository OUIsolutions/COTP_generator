
typedef struct COTPKey{
    char generated_sha[81];
    int interval;
    int password_size;
    bool allow_letters_on_passowrd;
}COTPKey;

COTPKey cotp_parse_key_string(const char *key);

void COTPParsedKey_represent(COTPKey *parsed_key);

void COTPKey_get_password(COTPKey *parsed_key, char *password, int *time_ramaing, long actual_time);

void COTPKey_object_create_key_string(char *key_string, COTPKey *parsed_key);

void cotp_get_password(char *password, int *time_ramaing, const char *key_string, long actual_time);