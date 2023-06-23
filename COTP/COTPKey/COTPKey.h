
typedef struct COTPKey{
    char generated_sha[81];
    int interval;
    int password_size;
    bool allow_letters_on_passowrd;
}COTPKey;

COTPKey cotp_parse_key(const char *key);

void COTPParsedKey_reprsent(COTPKey *parsed_key);

void COTPParsedKey_get_password(COTPKey *parsed_key, char *password, int *time_ramaing, long actual_time);

void cotp_get_password(char *password, int *time_ramaing, const char *key, long actual_time);