all: towerOfHanoi

towerOfHanoi: towerOfHanoi.o primlib.o
	gcc -fsanitize=address -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -fsanitize=address -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

towerOfHanoi.o: towerOfHanoi.c primlib.h

clean:
	-rm primlib.o towerOfHanoi.o towerOfHanoi
