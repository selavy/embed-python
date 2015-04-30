CC=gcc
CFLAGS=-Wall -Werror -g -O0
OBJS = main.o quote_source.o quote.o python_module_loader.o
INC = `python2.7-config --cflags` 
LIBS = `python2.7-config --ldflags`
EXE=simple

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS) $(INC)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(INC)
quote_source.o: quote_source.h quote_source.c
	$(CC) $(CFLAGS) -c quote_source.c $(INC)
quote.o: quote.h quote.c
	$(CC) $(CFLAGS) -c quote.c $(INC)
python_module_loader.o: python_module_loader.h python_module_loader.c
	$(CC) $(CFLAGS) -c python_module_loader.c $(INC)

.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS)
