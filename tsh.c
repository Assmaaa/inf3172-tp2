#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define MAX_NUMBER_OF_ARGUMENTS 64

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
    else if(ptr != argv) realpath(argv[0], filename); //relative path
    else strcat(filename, *argv); //absolute path

    pid = fork(); // creation of the child process

    if (pid > 0) {// IF PARENT
        do {
            wpid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            if (wpid == -1) { perror("error while waiting the pid of the child: "); exit(EXIT_FAILURE); }

            if (WIFSIGNALED(status)) fprintf(stdout, "status: killed by signal %d\n", WTERMSIG(status));
            else if (WIFSTOPPED(status)) fprintf(stdout, "status: stopped by signal %d\n", WSTOPSIG(status));
            else if (WIFCONTINUED(status)) fprintf(stdout, "status: continued\n");

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }else if (pid == 0) {// IF CHILD
        if(execv(filename, argv)) perror("error while launching sub-command: "); // execute the command with his param
        exit(0);
    }else fprintf(stderr, "Erreur! il y a eu un probleme lors du fork de processus!!");
}

int main(void) {
    int  exit = 0;		/* Exit condition */
    char line[4098] = "";	/* line containing the arguments */

    while (!exit) {
        printf("tsh>  ");
        fflush(stdin);
        if (fgets(line, sizeof(line), stdin) != NULL)
        {
            char* argv[MAX_NUMBER_OF_ARGUMENTS] = {NULL};
            parse(line, argv);
            char *command_str = argv[0];

            if(command_str == NULL) continue;
            else if (strcmp(command_str, "exit") == 0) exit = 1;
            else if(strcmp(command_str, "cdir") == 0) cdir();
            else if (strcmp(command_str, "cd") == 0) cd(argv);
            else execute(argv);// EXECUTE COMMAND WITH argv
        }
    }
    return EXIT_SUCCESS;
}
