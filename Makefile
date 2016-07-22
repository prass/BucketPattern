OBJS = main.o bucket.o

CC = gcc
CFLAGS = -g -Wall -Wextra -Wunused
INCS = -I.

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

clean:
	-rm $(OBJS)
	-rm main

.PHONY: clean all
