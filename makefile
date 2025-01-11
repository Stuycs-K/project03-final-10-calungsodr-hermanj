compile: host player
host: host.o 
	gcc -o host host.o 
player: player.o 
	gcc -o player player.o 
host.o: host.c host.h
	gcc -c host.c
player.o: player.c player.h
	gcc -c player.c
clean:
	rm -f *.o game
