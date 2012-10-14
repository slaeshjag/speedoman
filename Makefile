SOURCE = src/speedoman.c src/state.c src/movable.c src/level.c
LDFLAGS += -ldarnit 
BINARY = bin/speedoman
CFLAGS += -Wall -g -O0

default:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY) $(LDFLAGS)
	cd res && make

clean:
	rm -Rf bin
