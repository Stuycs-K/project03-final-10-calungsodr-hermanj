compile: game
run: game
	./game
game: player.o host.o semaphore.o
	gcc -o game player.o host.o semaphore.o
player.o: player.c player.h
	gcc -c player.c
host.o: host.c host.h semaphore.h
	gcc -c host.c
semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c
clean:
	rm -f *.o game
