// Encrypt / Decrypt String v1
// working attempt at caesar cipher

#include<stdio.h>
// calls main function
int main ()
{
    // limits character counts
    char array[100];
    int i,j,o;
    // gets input from user
    printf("enter a string \n");
    fgets(array, 100, stdin);
    // option to encrypt ot decrypt
    printf("choose your option \n");
    printf("*1:encryption\n");
    printf("*2:decryption\n");
    scanf("%d",&o);
    switch(o) {
    // "encrypts" string
    case 1:
    for (i=0;(i<100 && array[i]!='\0');i++)
    {
        if(array[i]==' ')
        {
            continue;
        }
        array[i]=array[i]+3;
    }
    printf("%s\n",array);
    break;
    // "decrypts" string
    case 2:
    for(j=0;(j<100 && array[j]!='\0');j++)
    {
        if(array[j]==' ')
        {
            continue;
        }
        array[j]=array[j]-3;
    }
    printf("%s\n",array);
    break;
    default:
    printf("error \n");
    }
    return 0;
}