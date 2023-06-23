

int private_ctop_sanitize_range(int value, int min, int max){
    if(value < min){
        return min;
    }
    if(value > max){
        return max;
    }
    return value;
}
void  private_ctop_format_num(char *result,int num,int num_size){
    char element[11] = {0};
    sprintf(element,"%d",num);
    int element_size = (int)strlen(element);
    int zeros_to_add = num_size -element_size;
    char zeros[10] = {0};
    for(int i = 0; i < zeros_to_add; i++){
        zeros[i]  = '0';
    }
    int result_size = zeros_to_add + element_size;
    sprintf(result,"%s%s",zeros,element);
    result[result_size] = '\0';
}

void  private_ctop_calc_sha_256_generating_string(char *hash_string, const char *input){
    uint8_t hash[SIZE_OF_SHA_256_HASH];

    calc_sha_256(hash, input, strlen(input));
    for (unsigned int i = 0; i < SIZE_OF_SHA_256_HASH; i++) {
        sprintf(hash_string + i * 2, "%02x", hash[i]);
    }
}

void  private_ctop_calc_sha_256_generating_number(char *hash_string, const char *input){
    uint8_t hash[SIZE_OF_SHA_256_HASH] = {0};

    calc_sha_256(hash, input, strlen(input));

    int hash_string_size = 0;
    for (unsigned int i = 0; i < SIZE_OF_SHA_256_HASH; i++) {

        char result[5] = {0};
        sprintf(result,"%d",hash[i]);
        sprintf((hash_string + hash_string_size), "%s", result);
        hash_string_size+= (int)strlen(result);

    }
}

void private_ctop_sub_str(char *result,const char *element,int start_point,int end_point){

    int result_size = 0;
    for(int i = start_point; i < end_point; i++){

        result[result_size] = element[i];
        result_size+=1;
    }
    result[result_size] ='\0';
}

int private_ctop_int_sub_str(const char *element,int start_point,int end_point){
    char result[10]= {0};
    private_ctop_sub_str(result,element,start_point,end_point);
    int result_formated;
    sscanf(result,"%d",&result_formated);
    return result_formated;
}


