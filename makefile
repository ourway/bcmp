test:
	make build;
	make clean;

build:
	c99 -pedantic -Wall -Werror -O3 -c bcmp.c
	c99 -pedantic -Wall -Werror -O3 bcmp.o -o bcmp

clean:
	rm *.o
