// Encrypt / Decrypt String v2
// updated caesar cipher:
    // 1. practice: "normalize input before processing it"
    // 2. introduce modulo 26 into character shifts
    // 3. implement "don't repeat yourself" (DRY) for shift algorithm
    // 4. validate menu choice (encryption/decryption)
    // 5. use constants instead of magic numbers
    // 6. make shift configurable

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// limits character count
#define MAX_LENGTH 100

// calls main function
int main(void)
{
    char array[MAX_LENGTH];
    int i;
    int option;
    int shift;

    // gets string from user
    printf("Enter a string: ");
    if (fgets(array, MAX_LENGTH, stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // remove newline added by fgets()
    array[strcspn(array, "\n")] = '\0';

    // gets encryption/decryption option
    printf("Choose your option:\n");
    printf("1: Encryption\n");
    printf("2: Decryption\n");

    if (scanf("%d", &option) != 1) {
        printf("Invalid option.\n");
        return 1;
    }

    if (option != 1 && option != 2) {
        printf("Invalid option.\n");
        return 1;
    }

    // gets shift amount
    printf("Enter shift amount: ");

    if (scanf("%d", &shift) != 1) {
        printf("Invalid shift amount.\n");
        return 1;
    }

    // converts decryption into negative shift
    if (option == 2) {
        shift = -shift;
    }

    // keeps shift within 0-25 range
    shift = shift %26;

    // encrypt/decrypt each character
    for (i = 0; array[i] != '\0'; i++)
    {
        if (array[i] >= 'a' && array[i] <= 'z')
        {
            array[i] = 'a' + (array[i] - 'a' + shift + 26) % 26;
        }
        else if (array[i] >= 'A' && array[i] <= 'Z')
        {
            array[i] = 'A' + (array[i] - 'A' + shift + 26) % 26;
        }
    }

    printf("result: %s\n", array);

    return 0;
}