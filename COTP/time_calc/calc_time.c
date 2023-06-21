

int ctop_minutes(long minutes){
    return minutes * 60;
}
int ctop_hours(long hours){
    return ctop_minutes(60) * hours;
}
int ctops_days(long days){
    return ctop_hours(24) * days;
}
