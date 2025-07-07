# Nom du programme final
#pour compiler main.c en main.o
#pour compiler sauv.c en sauv.o
prog: main.o sauv.o
	gcc -o prog main.o sauv.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.o: main.c sauv.h
	gcc -c main.c

sauv.o: sauv.c sauv.h
	gcc -c sauv.c

clean:
	rm -f *.o prog
