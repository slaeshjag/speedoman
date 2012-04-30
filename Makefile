SOURCE = src/speedoman.c src/state.c
LDFLAGS += -ldarnit 
BINARY = bin/speedoman
CFLAGS += -I./include

default:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY) $(LDFLAGS)
	cd tools && make
	cd res && make

clean:
	rm -Rf bin
	cd tools && make clean
