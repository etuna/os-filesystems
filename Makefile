CC = gcc
CFLAGS = -o fs304
LDFLAGS = -lm

all:
	$(CC) $(CFLAGS) fs304.c $(LDFLAGS)
clean:
	rm -rf ./a.out


