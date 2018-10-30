
#include "intqueue.h"
/* the actual queue memory-- */
static IntQueue q1obj,q2obj;

int main()
{
  int i;
  /* NOTE: very important to have memory under ptrs!! */
  IntQueue *q1 = &q1obj;	/* we set up pointers to queue mem objects */
  IntQueue *q2 = &q2obj;	   /* Now use these ptrs as representing their objs */

  init_i_queue(q1, 6); 
  init_i_queue(q2, 6);

  printf("put 1, 2 in q1, dequeue and print: ");
  i_enqueue(q1,1);
  i_enqueue(q1,2);
  printf("dequeue one:");
  printf(" %d\n", i_dequeue(q1));

  printf("put 6 ints in queue (causing overflow) in q1:\n");
  i_enqueue(q1,3);
  i_enqueue(q1,4);
  i_enqueue(q1,5);
  if (i_enqueue(q1,6)<0) printf("overflow\n");
  if (i_enqueue(q1,7)<0) printf("overflow\n");
  if (i_enqueue(q1,8)<0) printf("overflow\n");

  printf("now dequeue 8 times, so last two should fail\n");
  for (i = 0 ;i < 8; i ++) {
      int x;

      printf("\nnow queue1 contains %d elements\n", i_queuecount(q1));
      x = i_dequeue(q1);
      if (x >= 0)
	  printf("dequeued %d  ", x);
      else
	  printf("dequeue failed, queue empty");
  }
  printf("\nnow queue1 contains %d elements\n", i_queuecount(q1));

  printf("enqueue 1,2 in q1, 3 in q2\n");

  i_enqueue(q1,1);
  i_enqueue(q1,2);
  i_enqueue(q2,3);

  printf("got %d from q2 \n", i_dequeue(q2));
  return 0;
}
