#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


static int check;
void sighandler(int);

int main () {
   check = 1;

   signal(SIGINT, sighandler);

   while(check) {
      printf("+\n");
      sleep(1); 
   }
   check = 1;
   while(check) {
      printf("-\n");
      sleep(1); 
   }
   return(0);
}

void sighandler(int signum) {

    if (signum == 2)
   {
    printf("\n");
    check = 0;
   }
}