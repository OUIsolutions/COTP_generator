

long ctop_minutes(int minutes){
    return minutes * 60;
}
long ctop_hours(int hours){
    return ctop_minutes(60) * hours;
}
long ctops_days(int days){
    return ctop_hours(24) * days;
}
