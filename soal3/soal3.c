#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <dirent.h>

int main() {
  pid_t child_id1, child_id2, child_id3;
  int status;

  child_id1 = fork();
  if (child_id1 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id1 == 0) {
    // this is child

    char *argv[] = {"mkdir", "-p", "indomie", NULL};
    execv("/bin/mkdir", argv);
  }

  while ((wait(&status)) > 0);
  child_id2 = fork();
  if (child_id2 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
   if (child_id2 == 0){
    // this is parent
    sleep(5);
    char *argv[] = {"mkdir", "-p", "sedaap", NULL};
    execv("/bin/mkdir", argv);
  }

  while ((wait(&status)) > 0);
  child_id3 = fork();
  if (child_id3 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
   if (child_id3 == 0) {
    char *argv[] = {"unzip", "/home/sin/modul2/jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
  }

  pid_t child_id5, child_id4, child_id6;

  while ((wait(&status)) > 0);
  child_id4 = fork();
  if (child_id4 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id4 == 0) {
    DIR *dir;
    struct dirent *input;
    dir = opendir("/home/sin/modul2/jpg");
    while((input = readdir(dir)) != NULL){
      if(input->d_type == DT_REG){
        pid_t child_id;
        child_id = fork();
        if (child_id < 0) {
          exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }
        if (child_id == 0) {
          char filename[300];
          sprintf(filename, "/home/sin/modul2/jpg/%s", input->d_name);
          char *argv[] = {"mv", filename, "/home/sin/modul2/sedaap", NULL};
          execv("/bin/mv", argv);
        }
      }
    }
  }

  while ((wait(&status)) > 0);
  child_id5 = fork();
  if (child_id5 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id5 == 0){
    // this is parent
    //sleep(5);
    char *argv[] = {"rsync", "-r", "/home/sin/modul2/jpg/", "/home/sin/modul2/indomie", NULL};
    execv("/usr/bin/rsync", argv);
  }

  while ((wait(&status)) > 0);
  child_id6 = fork();
  if (child_id6 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id6 == 0){
    // this is parent
    //sleep(5);
    char *argv[] = {"rm", "-r", "/home/sin/modul2/jpg", NULL};
    execv("/bin/rm", argv);
  }

  while ((wait(&status)) > 0);
  pid_t child_id7 = fork();
  if (child_id7 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id7 == 0){
    // this is parent
    //sleep(5);
    chdir("/home/sin/modul2/indomie/");
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba1.txt", "\;", NULL};
    execv("/usr/bin/find", argv);
  }

  while ((wait(&status)) > 0);
  pid_t child_id8 = fork();
  if (child_id8 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id8 == 0){
    // this is parent
    sleep(3);
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba2.txt", "\;", NULL};
    execv("/usr/bin/find", argv);
  }

  while ((wait(&status)) > 0);
  pid_t child_id9 = fork();
  if (child_id9 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if(child_id9 == 0){
    chdir("/home/sin/modul2/indomie/");
    char *argv[] = {"rm", "coba1.txt", "coba2.txt", NULL};
    execv("/bin/rm", argv);
  }

  else {
    while ((wait(&status)) > 0);
  }
}
