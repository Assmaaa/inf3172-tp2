
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char* argv[]){
    if(argc > 2) {
        fprintf(stdout, "<list> sans option pour afficher les fichiers." \
        " avec l'option -d pour afficher les repertoires");
    }
    else
    {
        if(argc == 1)
        {}
        else{
            char *param = argv[1];
            if(strcmp(param, "-d") == 0) {
                DIR *dp;
                struct dirent *ep;

                dp = opendir("./");
                if (dp != NULL) {
                    while (ep = readdir(dp))
                        puts(ep->d_name);
                    (void) closedir(dp);
                } else
                    perror("Couldn't open the directory");
            }
            else
                fprintf(stdout, "le parametre de <list> est invalide: essayer -d");
        }
    }
    return EXIT_SUCCESS;
}
