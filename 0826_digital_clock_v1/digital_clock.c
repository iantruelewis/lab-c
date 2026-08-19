// Digital clock build
// 1. Establish clock functionality
// 2. Connect to current time
// 3. Print digital clock graphics for user
// 4. High-five

#include<stdio.h>
#include<time.h>

int main ()
{
    time_t s,val =1;
    struct tm* current_time;

    // time in seconds
    s = time(NULL);
    // to get current time

    current_time = localtime(&s);

    // print time in minutes
    // house and seconds

    printf("%02d : %02d : %02d",current_time->tm_hour,current_time->tm_min,current_time->tm_sec);
    return 0;
}
