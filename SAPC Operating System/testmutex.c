/*
 * file: testmutex.c  First semaphore test: one semaphore, used as mutex
 * NOTE: Uncomment the semaphore calls for the real test.
 */

#include <stdio.h>
#include "tunistd.h"
/* #include "semaphore.h"  uncomment this when you have this API file */

void printline(char *s);
int main1(void);
int main2(void);
int main3(void);

int mutex;
int startflag;  /* in BSS, so initialized to 0 at startup */

int main1() 
{
  kprintf("startflag=%d\n", startflag);	/* debug verification */
  /*  mutex = sem_create(1); */
  startflag = 1;
  return 0;
}

int main2()
{
    char buf[2];
    char line[100];

    /* make sure main1 runs first and creates mutex */
    /* (Probably process 1 runs first and startflag=1 here) */
    while (startflag==0)
	write(TTY1,"a",1);

    printline("A requests mutex");
    /*    down(mutex); */
    printline("A has mutex, enter 2 chars: ");
    read(TTY1,buf,2);
    sprintf(line,"A got %s, releasing mutex", buf);
    printline(line);
    /* up(mutex); */
    return 0;
}

int main3()
{
    char buf[2];
    char line[100];

    /* make sure main1 runs first and creates mutex */
    while (startflag==0)
	write(TTY1,"b",1);

    printline("B requests mutex");
    /* down(mutex); */
    printline("B has mutex, enter 2 chars: ");
    read(TTY1,buf,2);
    sprintf(line,"B got %s, releasing mutex", buf);
    printline(line);
    /* up(mutex); */
    return 0;
}


void printline(char *s)
{
    write(TTY1, s, strlen(s)); 
    write(TTY1,"\r\n",2);
}





