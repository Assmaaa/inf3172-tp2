#define _XOPEN_SOURCE 1			/* Required under GLIBC for nftw() */
#define _XOPEN_SOURCE_EXTENDED 1	/* Same */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>

int is_directory(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int is_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode) || S_ISLNK(path_stat.st_mode);
}

int remove_directory(const char *fpath, const struct stat *sb, int typeflag, struct FTW *flag){
    if(is_file(fpath)) unlink(fpath);
    else if(is_directory(fpath)) rmdir(fpath);
    return 0; //no error
}

int main(int argc, char* argv[]){
    if(argc != 2) fprintf(stdout, "<rmall> prend un chemin relatif/absolu en parametre\n");
    else if (!argv[1] || access(argv[1], R_OK)) perror("ce parametre n'est pas accessbile: ");
    else if (nftw(argv[1], &remove_directory, 1, FTW_DEPTH)) perror("error occurred while removing directory: ");
    return EXIT_SUCCESS;
}
