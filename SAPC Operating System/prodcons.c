/* prodcons.c from class notes, edited to work in hw5 environment */
/* This uses semaphores in the normal way to share a buffer of
   As it runs, it records the sequence of producer "p" actions
   and consumer "c" actions in a global string "report".  When
   the consumer finishes, it writes out the string.  This way,
   the main run is not disturbed by i/o delays.
*/
#include <stdio.h>
#include "tunistd.h"
/* #include "semaphore.h" uncomment asap */
#include "intqueue/intqueue.h"

/* number of spots in shared buffer */
#define N 5
/* number of fake items to process */
#define NITEMS 30
/* size of delay to mimic producer/consumer work */
#define DELAYCOUNT 200000

/* globals set up by main1, used by main1 and main2 */
static int mutex, empty, full; 
/* for in-memory buffer of record of consumer/producer actions */
/* max report string length--need one [pxx] and one [cxx] per item */
#define MAXREPORT (100 + NITEMS*8)
static char report[MAXREPORT];
IntQueue buffer;

extern char *strcat(char *s1, const char *s2);  /* no strings.h header */
int main1(void);
int main2(void);
int main3(void);
void printline(char *s);
static void delay(void);

int main1()
{
    report[0] = 0;		/* start with empty string */
    init_i_queue(&buffer, N);   /* set up shared queue of N ints */
    mutex = sem_create(1);
    empty = sem_create(N);
    full = sem_create(0);
    return 0;
}

/* producer */
int main2()
{
    int item = 0;
    char msg1[20];

    /* do some output to make sure main1 runs before producer loop */
    printline("producer-start");

    while (++item < 30) {	/* producer loop */
	item++;			/* "produce" item */
	delay();		/* producer delay */
	down(empty);  /* claim empty spot */
	down(mutex);
	i_enqueue(&buffer, item);
	sprintf(msg1, "[p%d]", item);
	strcat(report,msg1);	/* indicate producer action */
	up(mutex);
	up(full);   /* signal filled-in spot */
    }
    return 2;
}

/* consumer */
int main3()
{
    int item = 0;
    char msg1[20];

    /* do some output to make sure main1 runs before consumer loop */
    printline("consumer-start"); /* make sure main1 runs first */

    while (item < NITEMS - 1) { /* consumer loop */
	down(full);
	down(mutex);
	item = i_dequeue(&buffer);
	sprintf(msg1,"[c%d]", item);
	strcat(report, msg1);  /* under mutex */
	up(mutex);
	up(empty);
	delay();   /* consumer "consuming" */
    }
    /* output report of c's and p's */
    printline(report);
    return 0;
}

/* little delay to mimic work on item for producer and consumer */
static void delay()
{
    int i;

    for (i=0;i<DELAYCOUNT; i++)
	;
}

void printline(char *s)
{
    write(TTY1, s, strlen(s)); 
    write(TTY1,"\r\n",2);
}




