

# SoalShiftSISOP20_modul2_B01

Soal Shift Modul 2
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)


### 1. Soal 1
##### Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:
#### e. Tidak boleh menggunakan fungsi system()
File *inibash.sh* disimpan pada direltori `/home/sin/modul2/`.
Kodenya :

```C
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

int checkBintang(char a[]){ //fungsi cek bintang atau bukan
  if(a[0] == '*'){
    return 1;
  }
  return 0;
}

int checkAngka(char a[]){ //fungsi cek angka atau bukan
  for(int i = 0; i < strlen(a); i++){
    if(a[i] < '0' || a[i] > '9'){
      return 0;
    }
  }
  return 1;
}

int main (int argc, char **argv){
  if (argc == 5){ // argumen yang masuk harus 5
    int arguments[4];
    for (int i = 1; i < 4; i++){
      if (checkAngka(argv[i])){
        arguments[i] = atoi(argv[i]); // convert argumen dari char ke int
        if (arguments[i] < 0) { //input harus positif
          printf("invalid input ke %d\n", i);
        }
      }
      else if (checkBintang(argv[i])) {// bila argumen yang diinput bintang maka ditandai dengan nilai -69
        arguments[i] = -69;
        }
      else{
        printf("invalid input ke %d\n", i);
        exit(EXIT_FAILURE);
      }
    }
      if (arguments[1] > 59 && arguments[2] > 59 && arguments[3] > 23) { // input tidak boleh melebihi batas
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
        if((tm->tm_sec == arguments[1] || arguments[1] == -69) && (tm->tm_min == arguments[2] || arguments[2] == -69) && (tm->tm_hour == arguments[3] || arguments[3] == -69)){// cek apakah waktu system sesuai dengan waktu yang diinputkan
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
```

### 2. Soal 2
Kami belum mengerjakan nomor 2 karena waktu yang kurang memadai
### 3. Soal 3
##### Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).
Kodenya :
```C
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

    char *argv[] = {"mkdir", "-p", "indomie", NULL}; //membuat direktori bernama indomie
    execv("/bin/mkdir", argv);
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  child_id2 = fork();
  if (child_id2 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
   if (child_id2 == 0){
    // this is parent
    sleep(5);// menunggu 5 detik untuk melakukan tugas berikutnya
    char *argv[] = {"mkdir", "-p", "sedaap", NULL};// membuat direktori sedaap
    execv("/bin/mkdir", argv);
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  child_id3 = fork();
  if (child_id3 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
   if (child_id3 == 0) {
    char *argv[] = {"unzip", "/home/sin/modul2/jpg.zip", NULL};// ekstrak jpg.zip
    execv("/usr/bin/unzip", argv);
  }

  pid_t child_id5, child_id4, child_id6;

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  child_id4 = fork();
  if (child_id4 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id4 == 0) {
    DIR *dir;
    struct dirent *input;
    dir = opendir("/home/sin/modul2/jpg");// membuka direktori jpg
    while((input = readdir(dir)) != NULL){// cek apakah dorektori jpg ada
      if(input->d_type == DT_REG){// cek tipe file apakah sebuah Regular File atau bukan
        pid_t child_id;
        child_id = fork();
        if (child_id < 0) {
          exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }
        if (child_id == 0) {
          char filename[300];
          sprintf(filename, "/home/sin/modul2/jpg/%s", input->d_name);// membuat string yang isinya direktori Refular File
          char *argv[] = {"mv", filename, "/home/sin/modul2/sedaap", NULL};// memindahkan file ke folder sedaap
          execv("/bin/mv", argv);
        }
      }
    }
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  child_id5 = fork();
  if (child_id5 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id5 == 0){
    // this is parent
    //sleep(5);
    char *argv[] = {"rsync", "-r", "/home/sin/modul2/jpg/", "/home/sin/modul2/indomie", NULL}; // menyalin semua direktori yang ada di direktori jpg/ ke direktori indomie/
    execv("/usr/bin/rsync", argv);
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  child_id6 = fork();
  if (child_id6 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id6 == 0){
    // this is parent
    //sleep(5);
    char *argv[] = {"rm", "-r", "/home/sin/modul2/jpg", NULL}; // menghapus direktori jpg
    execv("/bin/rm", argv);
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  pid_t child_id7 = fork();
  if (child_id7 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id7 == 0){
    // this is parent
    //sleep(5);
    chdir("/home/sin/modul2/indomie/");// menuju ke direktori indomie/
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba1.txt", "\;", NULL};// membuat file coba1.txt ke semua direktori yang ada di direktori indomie/
    execv("/usr/bin/find", argv);
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  pid_t child_id8 = fork();
  if (child_id8 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if (child_id8 == 0){
    // this is parent
    sleep(3);// menunggu selama 3 detik
    char *argv[] = {"find", ".", "-type", "d", "-exec", "touch", "{}/coba2.txt", "\;", NULL};// membuat file coba2.txt ke semua direktori yang ada di direktori indomie/
    execv("/usr/bin/find", argv); 
  }

  while ((wait(&status)) > 0);//menunggu proses sebelumnya selesai
  pid_t child_id9 = fork();
  if (child_id9 < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }
  if(child_id9 == 0){
    chdir("/home/sin/modul2/indomie/");//menuju direktori indomie/
    char *argv[] = {"rm", "coba1.txt", "coba2.txt", NULL}; // menghapus file coba1.txt dan coba2.txt dari direktori indomie/
    execv("/bin/rm", argv);
  }

  else {
    while ((wait(&status)) > 0); // do nothing
  }
}

```
