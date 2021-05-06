#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int main()
{
    int child;
    mkfifo("nevesitett", S_IRUSR | S_IWUSR);
    child = fork(); //uj processz krealasa

    if(child > 0){
        int i, a, b, c;

        FILE* bemenet = fopen("bemenet.txt", "r");
        if(bemenet == NULL){
            printf("Udvozlom!\nA fajl nem olvashato.\n");
            exit(-1);
        }

        fscanf(bemenet, "%d\n%d %d %d", &i, &a, &b, &c);
        printf("Udvozlom!\nA fajlbol %d db ertek lett kiolvasva.\n",i);

        int fd;
        fd = open("nevesitett", O_RDWR);
        write(fd, &a, sizeof(int));
        write(fd, &b, sizeof(int));
        write(fd, &c, sizeof(int));

        sleep(1);

        double x, y;
        read(fd, &x, sizeof(double));
        read(fd, &y, sizeof(double));

        close(fd);
        unlink("nevesitett");

        FILE *file;
        file = fopen("kimenet.txt", "w");
        fprintf(file, "%d %d %d %.2f %.2f", a, b, c, x, y);
        printf("\nEredmenyek mentve.");

    } else if(child == 0){
        int fd;
        int a,b,c;
	double x, y;

        fd = open("nevesitett", O_RDWR);
        read(fd, &a, sizeof(int));
        read(fd, &b, sizeof(int));
        read(fd, &c, sizeof(int));

        x = (-b + sqrt(b*b-4*a*c)) / (2*a);
        y = (-b - sqrt(b*b-4*a*c)) / (2*a);

        printf("\nA masodfoku egyenlet megoldo keplete:(-b +- sqrt(b*b - 4*a*c) ) / (2*a)\n");
        printf("\nA megoldasok:\nx1: %.1f  es  x2: %.1f\n", x, y);

        write(fd, &x, sizeof(double));
        write(fd, &y, sizeof(double));

        close(fd);
    }

    return 0;
}
