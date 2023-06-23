
typedef struct CTopParsedKey{
    char generated_sha[81];
    int interval;
    int password_size;
    bool allow_letters_on_passowrd;
}CTopParsedKey;

CTopParsedKey ctop_parse_key(const char *key);

void CTopParsedKey_reprsent(CTopParsedKey *parsed_key);

void CTopParsedKey_get_password(CTopParsedKey *parsed_key,char *password,int *time_ramaing,long actual_time);

void ctop_get_password(char *password,int *time_ramaing,const char *key,long actual_time);