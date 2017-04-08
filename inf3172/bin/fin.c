
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    char* validation_ptr;
    int num = strtol(argv[1], validation_ptr, 10);
    if(argc != 3)
        fprintf(stdout, "");
    else if(num <= 0 || *validation_ptr != NULL)
        fprintf(stdout, "la commande fin prend une valeur numerique superieur" \
                "a zero pour le nombre de ligne a lire et un chemin relatif/absolu vers le fichier\n");
    else
    {
        FILE *file = fopen(argv[2],"r");
        if(file == NULL)
        {
            fprintf(stdout, "Fichier introuvable\n");
            perror("error occurred while opening file");
        }
        else
        {
            char *buffer = NULL;
            int nb_of_line = 0;
            char c;

            while(getline(buffer, 0, file) != -1)
            {
                nb_of_line++;
            }
            int offset_line = nb_of_line - num;
            rewind(file);
            for(int i = 0; i < offset_line; i++)
                getline(buffer, 0, file);

            while ((c = getc(file)) != EOF)
                putchar(c);
            free(buffer);
            fclose(file);
        }
    }
    return EXIT_SUCCESS;
}
