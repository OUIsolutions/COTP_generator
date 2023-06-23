

int private_cotp_sanitize_range(int value, int min, int max);


void private_cotp_format_num(char *result, int num, int num_size);


void  private_cotp_calc_sha_256_generating_string(char *hash_string, const char *input);

void  private_cotp_calc_sha_256_generating_number(char *hash_string, const char *input);


void  private_cotp_sub_str(char *result, const char *element, int start_point, int end_point);

int private_cotp_int_sub_str(const char *element, int start_point, int end_point);


