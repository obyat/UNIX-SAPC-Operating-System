
#include "intqueue.h"                        

static int addone(IntQueue *queue, int i);        /* auxiliary function */     

/* ------------------------------------------------------------------------ */
/* algorithm from "Data structure and algorithm" - AHU  p62 */
/* that algorithm actually use maxlength - 1 elements, so we have to add 1 */
/* to the max_ints in order to let the caller use exactly max_ints element*/

/* note: caller is responsible for having allocated space for queue */
int init_i_queue(IntQueue *queue, int max_objs)
{
  int maxlength = max_objs + 1 ;             /* waste a slot */

  if (maxlength > MAXQBUF) {           /* enough memory ? */
    printf("Error : not enough buffer for this queue !\n");
    return FALSE;
  }
  else {
    queue->front = 1;
    queue->rear = maxlength;                 
    queue->count = 0;
    queue->max = maxlength;                  /* actually use maxlength memory */
    return TRUE;
  }
}

/* ------------------------------------------------------------------------ */
/* algorithm from "Data structure and algorithm" - AHU  p62 */
int i_emptyque(IntQueue *queue)
{
  if (addone(queue,queue->rear) == queue->front)
    return TRUE;
  else
    return FALSE;
}


 /* ------------------------------------------------------------------------ */
/* algorithm from "Data structure and algorithm" - AHU  p62 */

int i_enqueue(IntQueue *queue, int x)
{
  if (x < 0)
    return BADELTVAL;

  if (addone(queue,addone(queue,queue->rear)) == queue->front)
    return FULLINTQUE;

  queue->rear = addone(queue,queue->rear);
  queue->contents[queue->rear] = x;
  queue->count++;
  return 0;           /* successful */
}

/* ------------------------------------------------------------------------ */
/* algorithm from "Data structure and algorithm" - AHU  p62 */
int i_dequeue(IntQueue *queue)
{
  int x;

  if (i_emptyque(queue)) {
    return EMPTYINTQUE;
  }
  x = queue->contents[queue->front];
  queue->front = addone(queue,queue->front);
  (queue->count) --;
  return x;
}

/* ------------------------------------------------------------------------ */
int i_queuecount(IntQueue *queue)
{
  return queue->count;
}


/* ------------------------------------------------------------------------ */
/* algorithm from "Data structure and algorithm" - AHU  p62 */
/* function that return next index */
static int addone(IntQueue *queue, int ind)
{
  return (ind+1) % queue->max;
}

