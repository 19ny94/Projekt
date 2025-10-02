all: main

CC = clang
override CFLAGS += -std=c11 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-unused-result -Wno-unknown-pragmas -pedantic -lm

.PHONY: run clean

main: projekt.c
	$(CC) $(CFLAGS) -O0 ./*.c -o "$@"

main-debug: projekt.c
	$(CC) $(CFLAGS) -O0 -g ./*.c -o "$@"

run: projekt
	./projekt $(ARGS)

clean:
	rm -f main main-*
