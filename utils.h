#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

void parse(char *line, char **argv)
{
    char delimiters[] = "\n ";
    char* token = strtok(line, delimiters);

    while (token != NULL) {
        *argv++ = token; // COPY TOKEN TO ARGUMENT
        token = strtok(NULL, delimiters);
    }
    *argv = (char*) '\0'; // MARK THE END OF THE ARGUMENT LIST
}

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

void cdir() {
    long path_max;
    size_t size;
    char *buf, *ptr;

    path_max = pathconf(".", _PC_PATH_MAX);
    if (path_max == -1) size = 1024;
    else if (path_max > 10240) size = 10240;
    else size = path_max;

    for (buf = ptr = NULL; ptr == NULL; size *= 2)
    {
        if ((buf = realloc(buf, size)) == NULL) {
            perror("Error (re)allocating memory for path name:");
            exit (1);
        }

        ptr = getcwd(buf, size);
        if (ptr == NULL && errno != ERANGE) perror("error, the string is larger than the buffer: ");
    }
    fprintf(stdout,"%s\n", ptr);
    free (buf);
}

void cd(char **argv) {
    if(argv[1] == NULL || strcmp(argv[1], "~") == 0 ) chdir(getenv("HOME"));
    else if (chdir(argv[1]) != 0) fprintf(stdout, "Repertoire introuvable\n");
}
#endif //UTILS_H
