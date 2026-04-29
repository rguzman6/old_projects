OBJS = guzman_rachel_assn3.o guzman_calendar.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXE = calendar

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

guzman_rachel_assn3.o: guzman_calendar.h
	$(CC) $(CFLAGS) guzman_rachel_assn3.cpp

guzman_calendar.o: guzman_calendar.h
	$(CC) $(CFLAGS) guzman_calendar.cpp

clean:
	rm *.o *~ $(EXE) -v
