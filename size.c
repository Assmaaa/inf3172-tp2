
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ftw.h>
#include "utils.h"

static unsigned int total = 0;
static unsigned int qte = 0;
static char path[4096 + 1]= "";

int sum(const char *fpath, const struct stat *sb, int typeflag) {
    if(is_file(fpath)) {
        total += sb->st_size;
        qte++;
    }
    return 0;// no error
}

int main(int argc, char* argv[]){
    if(argc != 2)
        fprintf(stdout, "<size> prend un chemin relatif/absolu en parametre");
    else
    {
        if (!argv[1] || access(argv[1], R_OK)) perror("ce parametre n'est pas accessbile");
        else if (ftw(argv[1], &sum, 1)) perror("error occurred in ftw");
        realpath(argv[1],path);
        fprintf(stdout, "Le répertoire %s contient %d fichiers pour un total de %d octets.", path, qte, total);
    }
    return EXIT_SUCCESS;
}
