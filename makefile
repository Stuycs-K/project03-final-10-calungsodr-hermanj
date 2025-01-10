compile: game
host: hosts
	./hosts
player: playerss
	./players
hosts: host.o
	gcc -o hosts host.o
playerss: player.o
	gcc -o players player.o
player.o: player.c player.h
	gcc -c player.c
host.o: host.c host.h
	gcc -c host.c
clean:
	rm -f *.o game
