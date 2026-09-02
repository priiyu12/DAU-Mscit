//202412048 Harsh Mehta

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exit-utils.h"
#include "simplesh-utils.h"

#define MAX_CMDS 20
#define MAX_ARGS 100

void parsePipeline(char *commandLine, char *cmds[], int *numCmds) {
  *numCmds = 0;
  char *saveptr;
  char *token = strtok_r(commandLine, "|", &saveptr);
  while (token != NULL && *numCmds < MAX_CMDS) {
    cmds[(*numCmds)++] = strdup(token);
    token = strtok_r(NULL, "|", &saveptr);
  }
}

void parseCommandArgs(char *command, char *argv[]) {
  int argc = parseCommandLine(command, argv, MAX_ARGS);
  argv[argc] = NULL;
}

int main(int argc, char *argv[]) {
  while (true) {
    char commandLine[kMaxCommandLength + 1];
    readCommand(commandLine, sizeof(commandLine) - 1);
    if (feof(stdin)) break;

    char *pipelineCmds[MAX_CMDS];
    int numCmds = 0;
    parsePipeline(commandLine, pipelineCmds, &numCmds);

    if (numCmds == 0) continue;

    int pipefd[2], prevfd = -1;
    pid_t pids[MAX_CMDS];

    for (int i = 0; i < numCmds; i++) {
      char *argv[MAX_ARGS];
      parseCommandArgs(pipelineCmds[i], argv);
      if (argv[0] == NULL) continue;

      // Check for built-in
      if (numCmds == 1 && handleBuiltin(argv)) {
        continue;
      }

      if (i < numCmds - 1) {
        pipe(pipefd); // creating pipe
      }

      pid_t pid = forkProcess();
      if (pid == 0) {
        if (i > 0) {
          dup2(prevfd, STDIN_FILENO);
          close(prevfd);
        }
        if (i < numCmds - 1) {
          close(pipefd[0]); 
          dup2(pipefd[1], STDOUT_FILENO); 
          close(pipefd[1]);
        }

        execvp(argv[0], argv);
        fprintf(stderr, "%s: Command not found\n", argv[0]);
        exit(1);
      } else {
        pids[i] = pid;
        if (prevfd != -1) close(prevfd);
        if (i < numCmds - 1) {
          close(pipefd[1]);
          prevfd = pipefd[0];
        }
      }
    }

    for (int i = 0; i < numCmds; i++) {
      waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < numCmds; i++) {
      free(pipelineCmds[i]);
    }
  }

  printf("\n");
  return 0;
}
