#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int main()
{

    int file = open("S7KTW0.txt",O_RDWR);

    if (file > 0)
    {
        printf("Sikeres beolvasas\n\n");
    }
    else
    {
        printf("Hiba tortent a fajl beolvasasnal\n");
    }

    char txt[54];
    ssize_t x = read(file,&txt,54);

    if (x < 0) printf("Hiba tortent a fajl kiolvasasnal\n");
    else printf("%s\nBeolvasott byte: %ld\n",txt,x);

    lseek(file,0,SEEK_SET);
    read(file,&txt,54);

    ssize_t w = write(1,&txt,54);
    if(w < 0) printf("Hiba a kiiratasnal\n");
    else printf("\nKiirt byte mennyiseg: %ld",w);


    return 0;
}
