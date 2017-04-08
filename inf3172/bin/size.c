
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ftw.h>

static unsigned int total = 0;

int sum(const char *fpath, const struct stat *sb, int typeflag) {
    total += sb->st_size;
    return 0;// no error
}

int main(int argc, char* argv[]){
    if(argc != 2)
        fprintf(stdout, "<size> prend un chemin relatif/absolu en parametre");
    else
    {
        if (!argv[1] || access(argv[1], R_OK)) perror("ce parametre n'est pas accessbile");
        else if (ftw(argv[1], &sum, 1)) perror("error occurred in ftw");
    }
    return EXIT_SUCCESS;
}
