CC = gcc
CFLAGS =
OBJECTS = pSync.o
INCFLAGS = 
LDFLAGS =
LIBS =  -lpthread

all: pSync

PThreads: $(OBJECTS)
	$(CC) -o pSync $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f pSync.o, pSync