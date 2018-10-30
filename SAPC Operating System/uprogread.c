/* uprogread.c: simple test with read */
#include <stdio.h>
#include "tunistd.h"
#include "tty_public.h"

#define MILLION 1000000
#define DELAY (400 * MILLION)
int main1(void);
int main2(void);
int main3(void);

int main1()
{
  int i;

  write(TTY1,"aaaaaaaaaa",10);
  fprintf(TTY1, "zzz");
  for (i=0;i<DELAY;i++)	/* enough time to drain output q */
    ;
  write(TTY1,"AAAAAAAAAA",10);	/* see it start output again */
  return 2;
}

int main2()
{
  char buf[10];
  write(TTY1,"enter:",6);
  read(TTY1,buf,2);
  write(TTY1,"bbbbbbbbbb",10);
  return 4;
}

int main3()
{
  write(TTY1,"cccccccccc",10);
  return 6;
}
