CC = gcc
CFLAGS = -g -Wall -Werror

all: proxy

proxy: proxy.o
	$(CC) $(LFLAGS) -o $@ $?

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

clean:
	rm -rf *.o
	rm proxy
