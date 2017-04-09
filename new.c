#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
 if(argc != 2)
     fprintf(stdout, "la commande new prend un nom de fichier en parametre\n");
 else
 {
     mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
     char *filename = argv[1];
     creat(filename, mode);
 }
    return EXIT_SUCCESS;
}