#  build queue package and its testbed

PC_INC = $(SAPC_TOOLS)/include

PC_CC   = $(SAPC_GNUBIN)/i386-gcc
PC_CFLAGS = -g -Wall -Wno-implicit -Wshadow -I$(PC_INC)
PC_LD   = $(SAPC_GNUBIN)/i386-ld

CC = gcc
CFLAGS = -g -Wall -Wno-implicit -Wshadow 

all: testqueue

intqueue.o: intqueue.h intqueue.c
testqueue.o: intqueue.h testqueue.c

testqueue: intqueue.o testqueue.o
	$(CC) $(CFLAGS)  -o testqueue testqueue.o intqueue.o 

intqueue.opc: intqueue.h intqueue.c
	$(PC_CC) $(PC_CFLAGS) -I$(PC_INC) -c -o intqueue.opc intqueue.c

clean:
	 rm -f  *.o testqueue

