compile: game
run: game
	./game
game: player.o host.o
	gcc -o game player.o host.o
player.o: player.c player.h
	gcc -c player.c
host.o: host.c host.h
	gcc -c host.c
clean:
	rm -f *.o game
