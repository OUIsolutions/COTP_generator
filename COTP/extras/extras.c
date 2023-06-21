

int private_ctop_format_range(int value,int min, int max){
    if(value < min){
        return min;
    }
    if(value > max){
        return max;
    }
    return value;
}

char * private_ctop_format_num(int num,int num_size){

    char element[10] = {0};
    sprintf(element,"%d",num);
    int element_size = (int)strlen(element);
    int zeros_to_add = num_size -element_size;
    char zeros[10] = {0};
    for(int i = 0; i < zeros_to_add; i++){
        zeros[i]  = '0';
    }
    int result_size = zeros_to_add + element_size;
    char *result = malloc(result_size+2);
    sprintf(result,"%s%s",zeros,element);
    result[result_size] = '\0';
    return result;

}

char * private_ctop_sub_str(const char *element,int start_point,int end_point){
    char *result = malloc(end_point - start_point +2);
    int result_size = 0;
    for(int i = start_point; i < end_point; i++){
        result[result_size] = element[i];
        result_size+=1;
    }
    result[result_size] ='\0';
    return result;
}

int private_ctop_int_sub_str(const char *element,int start_point,int end_point){
    char *result = private_ctop_sub_str(element,start_point,end_point);
    int result_formated;
    sscanf(result,"%d",&result_formated);
    free(result);
    return result_formated;
}