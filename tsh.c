#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * FUNCTION: PARSE COMMAND LINE
 */
void parse(char *line, char **argv)
{
    // DEFINE DELIMITER HERE
    char delimiters[] = "\n ";

    // SPLIT LINE BY DELIMITER, USE char *strtok(char *str, const char *delim)
    char* token = strtok(line, delimiters);

    // WHILE THERE IS TOKEN
    while (token != NULL) {
        *argv++ = token; // COPY TOKEN TO ARGUMENT
        token = strtok(NULL, delimiters);
    }
    *argv = (char*) '\0'; // MARK THE END OF THE ARGUMENT LIST
}

void cdir()
{
    long path_max;
    size_t size;
    char *buf;
    char *ptr;


    path_max = pathconf(".", _PC_PATH_MAX);
    if (path_max == -1)
        size = 1024;
    else if (path_max > 10240)
        size = 10240;
    else
        size = path_max;


    for (buf = ptr = NULL; ptr == NULL; size *= 2)
    {
        if ((buf = realloc(buf, size)) == NULL)
        {
            puts ("Error (re)allocating memory");
            exit (1);
        }

        ptr = getcwd(buf, size);
        if (ptr == NULL && errno != ERANGE)
        {
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error!! the string is larger than the buffer.");
            fprintf(stderr,"Error getting the path: %s\n", strerror(errno));
        }

    }
    fprintf(stdout,"%s", ptr);
    free (buf);
}

/*
 * FUNCTION: EXECUTE COMMAND
 */
void execute(char **argv)
{
    // DEFINE PID AND STATUS
    pid_t pid;
    int status;
    char *envp[] = { NULL };
    //	FORK
    pid = fork();

    if (pid > 0) // IF PARENT
        pid = wait(&status);// WAIT THE CHILD INFINITELY
    else if (pid == 0) // IF CHILD
        execvp(*argv, argv); // EXECUTE THE COMMAND WITH argv
    else // ERROR
        fprintf(stderr, "Erreur! il y a eu un probleme lors du fork de processus!!");
}



void cd(char **argv) {
    if(argv[1] == NULL || strcmp(argv[1], "~") == 0 )
        chdir(getenv("HOME"));
    else {
        if (chdir(argv[1]) != 0)
            fprintf(stdout, "Repertoire introuvable\n");
    }
}

/*
 * FUNCTION: MAIN
 */
int main(void)
{
    int  exit = 0;		/* Exit condition */
    char line[1024];	/* line containing the arguments */

    // WHILE NOT EXIT
    while (!exit) {
        // PRINT THE SHELL HEADER
        printf("tsh>  ");

        // IF USER ENTERED A LINE FROM stdin
        if (fgets(line, sizeof(line), stdin) != NULL)
        {
            // DECLARE ARGUMENTS argv (MAX 64)
            char* argv[64] = {NULL};

            // PARSE THE LINE AND STORE ARGUMENTS IN argv
            parse(line, argv);
            // IF FIRST ARGUMENT IN LINE IS EXIT
            char *command_str = argv[0];
            if (strcmp(command_str, "exit") == 0) {
                // EXIT MAIN PROGRAM
                exit = 1;//is exit
            }
            else if(strcmp(command_str, "cdir") == 0){
                cdir();
            }
            else if (strcmp(command_str, "cd") == 0){
                cd(argv);
            }
            else // EXECUTE COMMAND WITH argv
            {
                execute(argv);
            }

        }
    }
    return EXIT_SUCCESS;
}
