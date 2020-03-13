#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int checkBintang(char a[]){
  if(a[0] == '*'){
    return 1;
  }
  return 0;
}

int checkAngka(char a[]){
  for(int i = 0; i < strlen(a); i++){
    if(a[i] < '0' || a[i] > '9'){
      return 0;
    }
  }
  return 1;
}

int main (int argc, char **argv){
  if (argc == 5){
    int arguments[4];
    for (int i = 1; i < 4; i++){
      if (checkAngka(argv[i])){
        arguments[i] = atoi(argv[i]);
        if (arguments[i] < 0) {
          printf("invalid input ke %d\n", i);
        }
      }
      else if (checkBintang(argv[i])) {
        arguments[i] = -69;
        }
      else{
        printf("invalid input ke %d\n", i);
        exit(EXIT_FAILURE);
      }
    }
      if (arguments[1] >= 59 && arguments[2] >= 59 && arguments[3] >= 23) {
        printf("invalid input\n");
        exit(EXIT_FAILURE);
      }

      pid_t pid, sid;        // Variabel untuk menyimpan PID

      pid = fork();     // Menyimpan PID dari Child Process

      /* Keluar saat fork gagal
      * (nilai variabel pid < 0) */
      if (pid < 0) {
        exit(EXIT_FAILURE);
      }

      /* Keluar saat fork berhasil
      * (nilai variabel pid adalah PID dari child process) */
      if (pid > 0) {
        exit(EXIT_SUCCESS);
      }

      umask(0);

      sid = setsid();
      if (sid < 0) {
        exit(EXIT_FAILURE);
      }

      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      while (1) {
        // Tulis program kalian di sini
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);
        if((tm->tm_sec == arguments[1] || arguments[1] == -69) && (tm->tm_min == arguments[2] || arguments[2] == -69) && (tm->tm_hour == arguments[3] || arguments[3] == -69)){
          pid_t child_id;
          child_id = fork();

          int status;

          if (child_id == 0){
            char *argexe[] = {"bash", argv[4], NULL};
            execv("/bin/bash", argexe);
          }
        }
        sleep(1);
      }
  }
  else{
    printf("argument invalid\n");
    exit(EXIT_FAILURE);
  }
}
