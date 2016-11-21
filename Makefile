all:
	gcc shell.c -o shell

run: shell
	./shell

clean:
	rm *~

