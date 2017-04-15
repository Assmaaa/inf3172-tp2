#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include "utils.h"
#define MAX_NUMBER_OF_ARGUMENTS 64

extern char **environ;
/*
 * FUNCTION: EXECUTE COMMAND
 */
void execute(char *argv[])
{
    pid_t pid, wpid;
    int status;

    char filename[4096+1] = "";
    char *ptr = strchr(argv[0],'/');//recherche du delimiter

    if(ptr == NULL) { // default path
        strcat(filename, getenv("HOME"));
        strcat(filename, "/inf3172/bin/");
        strcat(filename, argv[0]);
    }
    else if(ptr != argv) //relative path
    {
        realpath(argv[0], filename);
    }
    else strcat(filename, *argv); //absolute path

    pid = fork(); // creation of the child process

    if (pid > 0) {// IF PARENT
        do {
            wpid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            if (wpid == -1) { perror("waitpid"); exit(EXIT_FAILURE); }

            if (WIFSIGNALED(status)) printf("status: killed by signal %d\n", WTERMSIG(status));
            else if (WIFSTOPPED(status)) printf("status: stopped by signal %d\n", WSTOPSIG(status));
            else if (WIFCONTINUED(status)) printf("status: continued\n");

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }else if (pid == 0) {// IF CHILD
        if(execv(filename, argv)) perror(strerror(errno)); // EXECUTE THE COMMAND WITH argv
        exit(0);
    }else // ERROR
        fprintf(stderr, "Erreur! il y a eu un probleme lors du fork de processus!!");
}

/*
 * FUNCTION: MAIN
 */
int main(void)
{
    int  exit = 0;		/* Exit condition */
    char line[4098] = "";	/* line containing the arguments */

    // WHILE NOT EXIT
    while (!exit) {
        printf("tsh>  ");
        fflush(stdin);
        // IF USER ENTERED A LINE FROM stdin
        if (fgets(line, sizeof(line), stdin) != NULL)
        {
            char* argv[MAX_NUMBER_OF_ARGUMENTS] = {NULL};
            parse(line, argv);
            char *command_str = argv[0];

            //apply command
            if(command_str == NULL) continue;
            else if (strcmp(command_str, "exit") == 0) exit = 1;

            else if(strcmp(command_str, "cdir") == 0) cdir();

            else if (strcmp(command_str, "cd") == 0) cd(argv);

            else execute(argv);// EXECUTE COMMAND WITH argv
        }
    }
    return EXIT_SUCCESS;
}
