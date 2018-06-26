#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Size 50

void fail_function(char*, int*);
void kmp_algorithm(char*, char*, int*);

int main(void)
{
    char input_string[Max_Size] = "asisfjiababaababisjfis";
    char patten[Max_Size] = "ababaabab";
    int  failure[Max_Size];

    fail_function(patten, failure);
    kmp_algorithm(input_string, patten, failure);

    return 0;
}

void kmp_algorithm(char *string, char *patten, int *failure)
{
    int str_length    = strlen(string);
    int patten_length = strlen(patten);
    int i = 0;
    int index = 0;
    while(i < str_length)
    {
        if(string[i] == patten[index])
        {
            i++; index++;
        }
        else if(index == patten_length)
        {
            printf("begin:%d, finish:%d\n", i - patten_length + 1, i);
            index = failure[index - 1];
        }
        else if(index == 0)
        {
            i++;
        }
        else
        {
            index = failure[index - 1];
        }
        //printf("%d ",index);
    }
}

void fail_function(char *patten, int *failure)
{
    int patten_length = strlen(patten);

    failure[0] = 0; //initial fail function
    int i = 1;
    while(i < patten_length)
    {
        if(patten[i] == patten[failure[i-1]])
        {
            failure[i] = failure[i-1] + 1;
        }
        else
        {
            if(patten[i] == patten[0])
            {
                failure[i] = 1;
            }
            else
            {
                failure[i] = 0;
            }
        }
        i++;
    }

    //Display fail function
    //You can open it if you need it.
    //---------------------------------
    /*
    for(i = 0; i < patten_length; i++)
    {
        printf("%d ", failure[i]);
    }
    printf("\n");
    */
    //---------------------------------
}

