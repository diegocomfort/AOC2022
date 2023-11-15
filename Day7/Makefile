CC = clang
FLAGS = -Weverything

all: main

main: main.c day7.h
	$(CC) $(FLAGS) -o $@ $<

run:
	./main

clean: 
	rm main
