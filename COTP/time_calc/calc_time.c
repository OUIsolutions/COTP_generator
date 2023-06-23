

int ctop_minutes(int minutes){
    return minutes * 60;
}
int ctop_hours(int hours){
    return ctop_minutes(60) * hours;
}
int ctops_days(int days){
    return ctop_hours(24) * days;
}
