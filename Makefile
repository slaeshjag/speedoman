SOURCE = src/speedoman.c src/state.c
LDFLAGS += -ldarnit 
BINARY = bin/speedoman

default:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY) $(LDFLAGS)
	cd res && make

clean:
	rm -Rf bin
