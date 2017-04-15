
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "utils.h"

int main(int argc, char* argv[]){
    if(argc > 2) {
        fprintf(stdout, "<list> sans option pour afficher les fichiers." \
        " avec l'option -d pour afficher les repertoires");
    }
    else {
        DIR *dp;
        struct dirent *ep;

        dp = opendir("./");
        if (dp != NULL) {
            if (argc == 1) {
                fprintf(stdout, "Fichiers de ");
                cdir();
                while (ep = readdir(dp)) if (is_file(ep->d_name)) fprintf(stdout, "%s\n", ep->d_name);
            } else if (strcmp(argv[1], "-d") == 0) {
                fprintf(stdout, "Sous-repertoire de ");
                cdir();
                while (ep = readdir(dp)) {
                    if (is_directory(ep->d_name) && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
                            fprintf(stdout, "%s\n", ep->d_name);
                }
            } else fprintf(stdout, "le parametre de <list> est invalide: essayer -d");
            (void) closedir(dp);
        }else   perror("Couldn't open the directory");
    }
    return EXIT_SUCCESS;
}