all:
	gcc -o randfile randfile.c

run: all
	./randfile

clean:
	rm randfile
	rm numbers
