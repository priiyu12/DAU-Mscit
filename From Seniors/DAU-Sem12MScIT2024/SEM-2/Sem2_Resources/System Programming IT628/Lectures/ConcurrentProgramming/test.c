main(){
  int i; // for loop iterator
  pid_t pid[3]; // pids of child processes
  signal(SIGKILL, killhandler);
  signal(SIGCHLD, childhandler);
  for(i=0; i<3; i++){
    pid[i] = fork();
    if(!pid[i]){
        signal(SIGKILL, SIG_DFL);
        exit(5);
    }
  }
  for(i=0; i<3; i++){
    kill(pid[i], SIGKILL);
  } 
  sleep(5);
  printf("count = %d\n", count);
  exit(0);
}
