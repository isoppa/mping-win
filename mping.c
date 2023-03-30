#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <windows.h>
#define BUFSIZE 64
#define MAX_HOSTS 16
#define VERSION "2.0"

int main(int argc, char *argv[]) {
  FILE *fp;
  int i = 0;
  int j = 0;
  int host_count = 0;
  int count[MAX_HOSTS];
  int total_count = 0;
  int interval[MAX_HOSTS];
  char hosts[MAX_HOSTS][256];
  char cmd[BUFSIZE];
  char buf[BUFSIZE];
  char temp[BUFSIZE];
  char result[BUFSIZE];
  char *token;
  char *strend;
  char *find;
  time_t t;

  /* Enable Command Prompt Escape Sequencing */
    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode = 0;
    GetConsoleMode(stdOut, &consoleMode);
    consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdOut, consoleMode);

  printf("\x1b[39m");

  if (argc < 2 ) {
    fprintf(stderr, "usage: mping Destination address 1 [interval 1] [Destination address 2] [interval 2] ... [Destination address %d] [interval %d] \n", MAX_HOSTS, MAX_HOSTS);
    exit(-1);
  }

  for (i = 0; i < MAX_HOSTS; i++) {
    count[i] = 0;
    interval[i] = 0;
    hosts[i][0]='\0';
  }

  host_count = 0;
 
  for (i = 1; i < argc; i=i+2) {
    if (host_count >= MAX_HOSTS ){
    fprintf(stderr, " Too many hosts (hosts = %d). %d or less should be specified.\n", host_count, MAX_HOSTS);
    exit(-1);
    }

    strcpy(hosts[host_count], argv[i]);
    if (i + 1 >= argc ) {
      interval[host_count] = 1;
      host_count++;
      break;
    }
    interval[host_count] = strtol(argv[i + 1], &strend, 10);
    if (*strend != '\0') {
      i--;
      interval[host_count] = 1;
      host_count++;
      continue;
    }
    if (errno == ERANGE && (interval[i + 1] == LONG_MAX || interval[i + 1] == LONG_MIN)) {
      interval[host_count] = 1;
    }
    find = strstr(argv[host_count], "sinet.ad.jp");
    if (find != NULL) {
      if (interval[host_count] < 60) {
        interval[host_count] = 60;
      }
    }
    /*
    if (interval[host_count] < 1) {
      interval[host_count] = 1;
    }
    */
    host_count++;
  }
  
  /*  for (i = 0; i < host_count; i++)
  {
    printf("[%d/%d] hosts[%d]=%s, interval[%d]=%d\n", i, host_count, i, hosts[i], i, interval[i]);
  }
  */
  
   while (1) {
    printf("\x1b[39m");
    /* To print date, time and IP addresses */
   
    time(&t);
    if (j == 0) {
      system("cls");
      printf("\x1b[39m");
      printf("-----------------------------------------------\n");
     // printf("mping version %s:        (Destinations: %d)\n", VERSION, host_count);
      printf(" %2d destinations                 (version %s)\n", host_count, VERSION);
      //printf("mping version %s\n", VERSION);
      //printf("destinations: %d\n", host_count);
      printf("-----------------------------------------------\n");

      printf("  %s", ctime(&t));
      for (i = 0; i < host_count; i++) {
        printf("%20s", hosts[i]);
      }
      printf("\n");
      for (i = 0; i < host_count; i++) {
        if (count[i] > 0) {
          printf("\x1b[31m");
        } else {
          printf("\x1b[32m");
        }
        printf("%20d", count[i]);
      }
      printf("\x1b[39m");
      printf(" <- NG out of %d\n", total_count);
      fflush(stdout);
    }
    if (j++ > 10) {
      j = 0;
    }
    /* To throw ping */
    total_count++;
    for (i = 0; i < host_count; i++) {
      if (interval[i] > 0 && (total_count -1) % interval[i] == 0)
      {
        snprintf(cmd, BUFSIZE, "ping -n 1 %s", hosts[i]);
        if ((fp = popen(cmd, "r")) == NULL) {
          fprintf(stderr, "Can not exec ping. ");
          exit(-1);
        }
        strcpy(temp, "NG");
        do {
          token = fgets(buf, BUFSIZE, fp);
          if (strstr(buf, "TTL=") != NULL) {
            strcpy(temp, buf);
            break;
          }
        } while (token != NULL);
        pclose(fp);

        strcpy(result, "");
        if (temp[0] != 'N') {
          token = strtok(temp, " ");
          while (token != NULL) {
            token = strtok(NULL, " ");
            /*printf( "[%s]", token );*/
            if (strstr(token, "ms") != NULL) {
              printf("\x1b[32m");
              printf("%20s", token);
              break;
            }
          }
        } else {
          printf("\x1b[31m");
          printf("       *** Faild ***");
          count[i]++;
        }
      } else {
        printf("\x1b[39m");
        if (interval[i] > 0) {
          printf("  *** Skip (%3d) ***",  interval[i] - ((total_count - 1) % interval[i]));
        } else {
          printf("  *** Skip (Inf) ***");
        }
      }
      
    }
    printf("\n");
    fflush(stdout);
    
    sleep(1);
    
  }

  return 0;
}
