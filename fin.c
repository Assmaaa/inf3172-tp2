
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256
#define BUFFER_FULL (BUFFER_SIZE -1)

int main(int argc, char* argv[]){
    char* validation_ptr;
    long int num = strtol(argv[1], &validation_ptr, 10); //return 0L if not a number
    if(argc != 3) fprintf(stdout, "<fin> prend un entier et un fichier en arguments");
    else if(num <= 0 || *validation_ptr) fprintf(stdout, "la commande fin prend une valeur numerique superieur a zero pour le nombre de ligne a lire et un chemin relatif/absolu vers le fichier\n");
    else {
        FILE *file = fopen(argv[2],"r");
        if(file == NULL) {
            perror("error occurred while opening file: ");
        }
        else {
            char buffer[BUFFER_SIZE];
            int nb_of_line = 0;
            char c;

            while(fgets(buffer, BUFFER_SIZE, file) != NULL) if (strlen(buffer) < BUFFER_FULL) nb_of_line++;

            long int offset_line = nb_of_line - num;
            rewind(file);
            for(long int i = 0; i < offset_line; i++) while(strlen(fgets(buffer, BUFFER_SIZE, file)) == BUFFER_FULL);

            while ((c = fgetc(file)) != EOF) putchar(c);
            fclose(file);
        }
    }
    return EXIT_SUCCESS;
}
