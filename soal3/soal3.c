#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child_id1, child_id2;
  int status;

  child_id1 = fork();
  child_id2 = fork();

  if (child_id1 < 0 || child_id2 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id1 == 0) {
    // this is child

    char *argv[] = {"mkdir", "-p", "indomie", NULL};
    execv("/bin/mkdir", argv);
  }
  else if (child_id2 == 0){
    // this is parent
    sleep(5);

    char *argv[] = {"mkdir", "-p", "sedap", NULL};
    execv("/bin/mkdir", argv);
  }
  else {
    while ((wait(&status)) > 0);
    char *argv[] = {"unzip", "/home/sin/modul2/jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
  }

  pid_t child_id3, child_id4;

  while ((wait(&status)) > 0);
  child_id3 = fork();
  child_id4 = fork();

  if (child_id3 < 0 || child_id4 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  else if (child_id3 == 0) {
    // this is child
    char *argv[] = {"mv", "/home/sin/modul2/jpg/*/", "/home/sin/modul2/indomie/", NULL};
    execv("/bin/mv", argv);
  }
  else if (child_id4 == 0){
    // this is parent
    //sleep(5);
    while ((wait(&status)) > 0);
    char *argv[] = {"mv", "/home/sin/modul2/jpg/", "/home/sin/modul2/sedap/", NULL};
    execv("/bin/mv", argv);
  }
  else {

  }
}
