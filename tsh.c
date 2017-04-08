#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define MAX_NUMBER_OF_ARGUMENTS 64
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
            char* argv[MAX_NUMBER_OF_ARGUMENTS] = {NULL};
            parse(line, argv);
            char *command_str = argv[0];

            //apply command
            if (strcmp(command_str, "exit") == 0) exit = 1;

            else if(strcmp(command_str, "cdir") == 0) cdir();

            else if (strcmp(command_str, "cd") == 0) cd(argv);

            else execute(argv);// EXECUTE COMMAND WITH argv
        }
    }
    return EXIT_SUCCESS;
}
