CC=gcc
CFLAGS=-Wall -Werror -O0 -g
LIBS=
OBJS=main.o
EXE=forker

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)
.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXE)
