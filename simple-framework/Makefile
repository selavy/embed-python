CC=gcc
CFLAGS=-Wall -Werror -g
OBJS = main.o quote_source.o quote.o
EXE=simple

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
quote_source.o: quote_source.h quote_source.c
	$(CC) $(CFLAGS) -c quote_source.c
quote.o: quote.h quote.c
	$(CC) $(CFLAGS) -c quote.c

.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS)
