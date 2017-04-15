#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc != 2) fprintf(stdout, "<newdir> prend  uniquement un chemin relatif/absolu en parametre\n");
    else {
        struct stat st = {0};
        if (stat(argv[1], &st) == -1) mkdir(argv[1], 0700);
        else fprintf(stdout, "Impossible de creer le repertoire\n");
    }
    return EXIT_SUCCESS;
}
