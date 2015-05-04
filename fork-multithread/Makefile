CC=gcc
CFLAGS=-Wall -Werror -O0 -g
INC = `python2.7-config --cflags`
LIBS = `python2.7-config --ldflags` $(INC)
OBJS=main.o
EXE=forker

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)
.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXE)
