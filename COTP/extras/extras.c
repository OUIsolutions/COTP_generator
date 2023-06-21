

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