// Digital clock build v2
// 1. Establish clock functionality
// 2. Connect to current time
// 3. Print digital clock display for user
// 4. Add v2 updates:
    // test for unnecessary variables
    // error checking and failure handling
    // year, month, day to time output

#include<stdio.h>
#include<time.h>

int main ()
{
    // removed unecessary variable that wasn't being used: "val =1"
    time_t s;
    struct tm* current_time;
    // added "int test;" to check for unnecessary variables
        // int test;
    // compile with: gcc -Wall -Wextra program.c -o program
        // tests for unnecessary variables

    // time in seconds
    // added error checking
    s = time(NULL);
    if (s == (time_t)-1) {
        printf("Error Message\n");
        return 1;
    }
    
    // to get current time
    current_time = localtime(&s);
    // handle failure
    if (current_time == NULL) {
         printf("Error Message\n");
        return 1;
    }

    // print time in minutes, hours, and seconds
    // added stronger call formatting
    // added years, month, day
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
       current_time->tm_year + 1900,  // = current year
       current_time->tm_mon + 1,      // = current month 
       current_time->tm_mday,         // = current day of the month
       current_time->tm_hour,         // = current hour(s)
       current_time->tm_min,          // = current minute(s)
       current_time->tm_sec);         // = current second(s)
    return 0;
}