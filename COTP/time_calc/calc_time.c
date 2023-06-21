

long ctop_minutes(long minutes){
    return minutes * 60;
}
long ctop_hours(long hours){
    return ctop_minutes(60) * hours;
}
long ctops_days(long days){
    return ctop_hours(24) * days;
}
