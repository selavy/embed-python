CC=gcc
CFLAGS=-Wall -Werror -g -O0
LIBS=-lpthread

OBJS = main.o
EXE = quote_source

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(EXE) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) $(LIBS) -c main.c
.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXE)

