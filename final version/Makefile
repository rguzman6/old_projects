OBJS = guzman_rachel_assn4.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXE = tree

$(EXE):$(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

guzman_rachel_assn4.o:guzman_bst.h
	$(CC) $(CFLAGS) guzman_rachel_assn4.cpp

clean:
	rm *.o *~ $(EXE) -v
