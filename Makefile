CC = gcc
CFLAGS =
OBJECTS = processSync.o
INCFLAGS = -w
LDFLAGS =
LIBS =  -lpthread

all: processSync

processSync: $(OBJECTS)
	$(CC) -o processSync $(OBJECTS) $(LDFLAGS) $(LIBS)


.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o
	rm -f processSync
