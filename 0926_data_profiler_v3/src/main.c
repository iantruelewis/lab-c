// Data Profiler
// v3:
    // * translation units
    // * header files
    // * function declarations and definitions
    // * header guards
    // * linking
    // * interfaces
    // * makefiles
    // * responsibility separation
// // //

// imports standard I/O library
#include <stdio.h>

#include "csv.h"
#include "profiler.h"

// calls main funtion
// argc = argument count
// argv = argument vector
// argv[0] is conventionally the program name
// argv[1] is first argument supplied by user
int main(int argc, char *argv[])
{
    // checks that user supplied at least one argument
    if (argc < 2)
    {
        // %s is printf format specifier for a string
        // argv[0] contains program name
        printf("Usage: %s <file>\n", argv[0]);

        // non-zero return value indicates program terminated due to error
        return 1;
    }

    // opens file in read mode
    FILE *file = fopen(argv[1], "r");

    // a special NULL pointer value
    // used to represent "points to nothing valid"
    if (file == NULL)
    {
        printf("Could not open file.");

        // non-zero return value indicates program terminated due to error
        return 1;
    }

    // character buffer used to temporarily store each line read from the file
    char buffer[1024];

    // reads the files on line at a time
    // fgets() returns NULL when there are no more lines available
    if (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // CSV with no commas still contains one column, begin counting at 1
        int columns = csv_count_columns(buffer);

        // index used to examine each character in buffer
        int i = 0;

        // loops through characters in buffer
        // '\0' represents the null terminator, marks end of C string
        while (buffer[i] != '\0')
        {
            // checks whether current character is comma
            // == asks whether two values are equal
            if (buffer[i] == ',')
            {
                // each comma represents another column boundary
                // each comma increases column count
                buffer[i] = '\0';
                break;
            }

            // moves to the next characer in the buffer
            i++;
        }

        // reset index to search through header again
        i = 0;

        // loops through header a second time
        // looking for first comma to separate first column name
        while (buffer[i] != '\0')
        {
            // checks whether the current character is a comma
            if (buffer[i] == ',')
            {
                // replace comma with null terminator
                // changes where the first C string ends
                buffer[i] = '\0';

            // stop searching once first comma is found
                break;
            }

            // move to the next character
            i++;
        }

        // prints first column name
        // %s tells printf() that buffer contains a C string
        printf("Column 1: %s\n", buffer);

        // prints the number of columns discovered
        printf("Columns: %d\n", columns);
    }

    // number of data lines read from file
    int lines = profiler_count_lines(file);

    // prints the number of remaining lines
    printf("Lines: %d\n", lines);

    // closes file after finished using it
    // files should be explicitly closed when no longer needed
    fclose(file);

    //indicates successful prohram execution
    return 0;
}