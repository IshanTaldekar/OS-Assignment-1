#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {

    if (argc > 51) {   // validate that the number of arguments received from the terminal is less or equal to 50
        fprintf(stderr, "ERROR: The number of command arguments exceeds the threshold of 50 arguments...\n");
        exit(1);
    }

    if (argc == 1) {   // validate that commands were provided for the child to run.
        fprintf(stderr, "ERROR: No command to run...\n");
        exit(1);
    }

    pid_t child_pid;    // childs process id (unique identifier given to process)
    int child_status;   // information about whether the child was successfully created.
    char **args;    // null terminated array of arguments to pass to the execvp call
    struct rusage usage;
    int usage_report_status;

    switch (child_pid = fork()) {


        case 0:  // The code in this section can only be run by the child process.
            args = (char **) malloc(argc * sizeof(char *));
            int counter = 0;

            /* load arguments in the args variable */
            while (counter < argc) {
                args[counter] = argv[counter + 1];
                counter = counter + 1;
            }

            args[argc + 1] = (char *) NULL; // arguments must be null terminated
            execvp(args[0], args);

            // If execvp is successful, then the remaining two lines of code below will not execute.
            fprintf(stderr, "Error: execvp command not executed...\n");
            break;

        case -1:  // This code snippet runs if the fork fails for some reason.
            fprintf(stderr, "ERROR: fork() unsuccessful...");
            exit(1);

        default:  // This piece of code is run only by the parent.
            wait(&child_status);  // Wait for the child process to terminate.

            if (WIFEXITED(child_status)) {    // Ensuring that the child process terminated normally.
                usage_report_status = getrusage(RUSAGE_CHILDREN, &usage); // returns information on resource use stored in the 'usage' pointer.
                if (usage_report_status == -1) {
                    perror("Error: ");  // prints error message, if getrusage() call failed
                    return -1;
                } else {
                    printf("The child spent %ld.%06ld seconds in user mode.\n", (long int) (usage.ru_utime.tv_sec),
                           (long int) (usage.ru_utime.tv_usec));
|                    printf("The child spent %ld.%06ld seconds in kernel mode.\n", (long int) (usage.ru_stime.tv_sec),
                           (long int) (usage.ru_stime.tv_usec));
                }
            }
    }
    return 0;
}
