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
void execute(char *argv[])
{
    // DEFINE PID AND STATUS
    int link[2];
    if (pipe(link)==-1) fprintf(stderr, "error occurred in pipe()\n");

    pid_t parent = getpid();
    pid_t pid, wpid;
    char buffer[4096];
    int status;
    char* home = (char*) calloc((strlen("HOME=") + strlen(getenv("HOME"))+1),sizeof(char));
    strcat(home,"HOME=");
    strcat(home, getenv("HOME"));

    char* path = (char*) calloc((strlen("PATH=") + strlen(getenv("HOME"))+strlen("/inf3172/bin") + 1),sizeof(char));
    strcat(path,"PATH=");
    strcat(path,getenv("HOME"));
    strcat(path, "/inf3172/bin");
    char *envp[] = {home, path, NULL };
    //	FORK
    pid = fork();

    if (pid > 0) {// IF PARENT
        close(link[1]);//don't need to write
        int nbytes = read(link[0], buffer, sizeof(buffer));
        fprintf(stdout, "Output: (%.*s)\n", nbytes, buffer);
        while ((wpid = wait(&status)) > 0)
        {
            fprintf(stdout, "Exit status of %d was %d (%s)\n", (int)wpid, status,
                   (status > 0) ? "error!" : "successful");
        }

    }else if (pid == 0) {// IF CHILD
        close(link[0]);//don't need to read
        dup2 (STDOUT_FILENO, link[1]); //close the stdout and replace it for the pipe to write
        execve(*argv, argv, envp); // EXECUTE THE COMMAND WITH argv
        exit(0);
    }else // ERROR
        fprintf(stderr, "Erreur! il y a eu un probleme lors du fork de processus!!");
    free(path);
    free(home);
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
