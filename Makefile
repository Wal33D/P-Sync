CC = gcc
CFLAGS =
OBJECTS = pSync.o
INCFLAGS = -w
LDFLAGS =
LIBS =  -lpthread

all: pSync

pSync: $(OBJECTS)
	$(CC) -o pSync $(OBJECTS) $(LDFLAGS) $(LIBS)


.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o, pSync