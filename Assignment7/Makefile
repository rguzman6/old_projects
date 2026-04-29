OBJS = Assignment7.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXE = assignment7

$(EXE):$(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

Assignment7.o: LinkedList.h Stack.h Graph.h
	$(CC) $(CFLAGS) Assignment7.cpp

clean: 
	rm *.o *~ $(EXE) -v
