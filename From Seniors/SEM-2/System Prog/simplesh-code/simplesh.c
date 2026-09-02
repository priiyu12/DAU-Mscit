#include <stdlib.h>     // exit
#include <stdio.h>      // for printf
#include <stdbool.h>    // for bool, true, false
#include <string.h>     // for strchr, strcmp
#include <unistd.h>     // for fork, execve
#include <sys/wait.h>   // for waitpid
#include <errno.h>      // for errno
#include <signal.h>     // for signal
#include "exit-utils.h" // for exitIf, exitUnless
#include "simplesh-utils.h"

static void pullRest() {
  while (getchar() != '\n');
}

static char *skipSpaces(const char *str) {
  while (*str == ' ') str++;
  return (char *) str;
}

void runPipeline(char *stages[], int stageCount) {
  int prevfd = -1;
  pid_t pids[stageCount];

  for (int i = 0; i < stageCount; i++) {
    int pipefd[2];
    if (i < stageCount - 1) {
      exitIf(pipe(pipefd) == -1, 3, stderr, "pipe creation failed.\n");
    }

    pids[i] = forkProcess();
    if (pids[i] == 0) {
      // CHILD
      if (prevfd != -1) {
        dup2(prevfd, STDIN_FILENO);
        close(prevfd);
      }
      if (i < stageCount - 1) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
      }

      char *argv[kMaxArgumentCount + 1];
      parseCommandLine(stages[i], argv, sizeof(argv) / sizeof(argv[0]));
      execvp(argv[0], argv);
      fprintf(stderr, "%s: command not found\n", argv[0]);
      exit(1);
    }

    // PARENT
    if (prevfd != -1) close(prevfd);
    if (i < stageCount - 1) {
      close(pipefd[1]);
      prevfd = pipefd[0];
    }
  }

  // Wait for all children
  for (int i = 0; i < stageCount; i++) {
    waitpid(pids[i], NULL, 0);
  }
}

int parsePipeline(char *command, char *stages[], int maxStages) {
  int count = 0;
  char *stage = strtok(command, "|");
  while (stage != NULL && count < maxStages - 1) {
    stages[count++] = skipSpaces(stage);
    stage = strtok(NULL, "|");
  }
  stages[count] = NULL;
  return count;
}

static pid_t fgpid = 0; // 0 means no foreground process
static void reapProcesses(int sig) {
  pid_t pid;
  while (true) {
    pid = waitpid(-1, NULL, WNOHANG);
    if (pid <= 0) break;
    if (pid == fgpid) fgpid = 0;
  }

  exitUnless(pid == 0 || errno == ECHILD, kWaitFailed, stderr, "waitpid function failed");
}

static void waitForForegroundProcess(pid_t pid) {
  fgpid = pid;
  sigset_t empty;
  sigemptyset(&empty); // SIGCHLD is still blocked here
  while (fgpid == pid) {
    sigsuspend(&empty); // temporarily unblock everything, wait for signal
  }
  unblockSIGCHLD();
}

int main(int argc, char *argv[]) {
  signal(SIGCHLD, reapProcesses);

  while (true) {
    char command[kMaxCommandLength + 1];
    readCommand(command, sizeof(command) - 1);
    if (feof(stdin)) break;

    // Skip empty commands
    if (strlen(command) == 0) continue;

    // Check for pipeline
    if (strchr(command, '|') != NULL) {
      char *stages[kMaxArgumentCount + 1];
      int stageCount = parsePipeline(command, stages, sizeof(stages) / sizeof(stages[0]));
      runPipeline(stages, stageCount);
      continue; // Done handling this command
    }

    // Non-pipeline command
    char *argv[kMaxArgumentCount + 1];
    int count = parseCommandLine(command, argv, sizeof(argv) / sizeof(argv[0]));
    if (count == 0) continue;

    bool builtin = handleBuiltin(argv);
    if (builtin) continue;

    bool isbg = strcmp(argv[count - 1], "&") == 0;
    if (isbg) argv[--count] = NULL; // remove & from args

    blockSIGCHLD();
    pid_t pid = forkProcess();
    if (pid == 0) {
      unblockSIGCHLD();
      execvp(argv[0], argv);
      printf("%s: Command not found\n", argv[0]);
      exit(0);
    }

    if (isbg) {
      printf("%d %s\n", pid, command);
      unblockSIGCHLD();
    } else {
      waitForForegroundProcess(pid);
    }
  }

  printf("\n");
  return 0;
}
