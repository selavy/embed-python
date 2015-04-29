a.out: main.c
	gcc main.c `python2.7-config --cflags` `python2.7-config --ldflags`
	#gcc main.c -framework Python
.PHONY: clean
clean:
	rm -rf a.out
