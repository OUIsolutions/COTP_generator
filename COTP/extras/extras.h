

int private_ctop_sanitize_range(int value, int min, int max);


void private_ctop_format_num(char *result,int num,int num_size);


void  private_ctop_calc_sha_256_generating_string(char *hash_string, const void *input, size_t len);

void  private_ctop_calc_sha_256_generating_number(char *hash_string, const void *input, size_t len);

void  private_ctop_sub_str(char *result,const char *element,int start_point,int end_point);

int private_ctop_int_sub_str(const char *element,int start_point,int end_point);


