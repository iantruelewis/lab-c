#include "profiler.h"

int profiler_count_lines(FILE *file)
{
    char buffer[1024];
    int lines = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        lines++;
    }

    return lines;
}