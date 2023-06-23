
CTopParsedKey ctop_parse_key(const char *key){

    CTopParsedKey parsed_key = {0};
    int key_size = (int)strlen(key);
    int sha_size = key_size - CTOP_DESCRIPTION_SIZE;

    private_ctop_sub_str(
            parsed_key.generated_sha,
            key,
            0,
            sha_size
    );
    return parsed_key;
}

void CTopParsedKey_reprsent(CTopParsedKey *parsed_key){
    printf("generated sha: %s\n",parsed_key->generated_sha);

}