CC=gcc
SANITIZE=-pie -fPIC
TSAN=-fsanitize=thread $(SANITIZE)
MSAN=-fsanitize=memory
ASAN=-fsanitize=address
#SANITIZER=$(ASAN)
SANITIZER=
CFLAGS=-Wall -Werror -g -O0 $(SANITIZER)
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

