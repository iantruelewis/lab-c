// Data Profiler
// v1
// // //

// imports standard I/O library
#include <stdio.h>

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
        return 1;
    }

    // non-zero return value indicates program terminated due to error
    printf("File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");

    // a special NULL pointer value
    // used to represent "points to nothing valid"
    if (file == NULL)
    {
        printf("Could not open file.");
        return 1;
    }

    // character buffer used to temporarily store each line read from the file
    char buffer[1024];

    // number of lines read from the file
    int lines = 0;

    // reads the files on line at a time
    // fgets() returns NULL when there are no more lines available
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        lines++;
    }

    printf("Lines: %d\n", lines);

    // closes file after task complete
    fclose(file);

    // indicates successful execution
    return 0;
}
