OBJS = guzman_intBST.o source.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXE = tree

$(EXE):$(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

guzman_intBST.o: guzman_intBST.h
	$(CC) $(CFLAGS) guzman_intBST.cpp

souce.o: guzman_intBST.h
	$(CC) $(CFLAGS) source.cpp

clean:
	rm *.o *~ $(EXE) -v
