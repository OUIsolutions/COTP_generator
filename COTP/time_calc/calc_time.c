

int cotp_minutes(int minutes){
    return minutes * 60;
}
int copt_hours(int hours){
    return cotp_minutes(60) * hours;
}
int cotp_days(int days){
    return copt_hours(24) * days;
}
