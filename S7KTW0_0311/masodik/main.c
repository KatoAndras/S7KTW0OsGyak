#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

int system(const char *command);

int main()
{
    char gets(char* strptr);
    char strArray[64];
    gets(strArray);

    char cmdArray[32];
    strcpy(cmdArray, strArray);
    system(cmdArray);

    return 0;
}
