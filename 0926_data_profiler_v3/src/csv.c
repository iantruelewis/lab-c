#include "csv.h"

int csv_count_columns(const char *header)
{
    int columns = 1;
    int i = 0;

    while (header[i] != '\0')
    {
        if (header[i] == ',')
        {
            columns++;
        }

        i++;
    }

    return columns;
}