
#ifndef INTQUEUE_H
#define INTQUEUE_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define EMPTYINTQUE (-1)            /* if queue is empty */
#define FULLINTQUE  (-1)            /* if queue is full */
#define BADELTVAL (-2)              /* only non-negative ints as elements */

#define MAXQBUF 100         

typedef struct queue {      
  int contents[MAXQBUF];       /* objects in queue */
  int front;                   /* front index of queue */
  int rear;                    /* rear index of queue */
  int count;                   /* current numbers of element in queue */ 
  int max;                     /* actually use length */
} IntQueue;


/* functions prototype */
/* initialize a queue with max capacity max_ints, fill in pointed-to
   IntQueue structure (an empty one was provided by caller)-- */

extern int init_i_queue(IntQueue *, int max_ints);

/* add object (non-negative integer) to the specified queue--
   returns FULLINTQUE (-1)if q full */
extern int i_enqueue(IntQueue *, int);

/* take one object (non-negative integer) out of spec. queue, 
   rets EMPTYINTQUE (-1) if q empty */
extern int i_dequeue(IntQueue *);

/* report on how many ints in queue now */
extern int i_queuecount(IntQueue *);

/* returns TRUE or FALSE-- */
extern int i_emptyque(IntQueue *);

#endif 
