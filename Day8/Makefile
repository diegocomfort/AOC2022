CC = clang
FLAGS = -Weverything -ggdb3

all: main

main: main.c day8.h
	$(CC) $(FLAGS) -o $@ $<

reset: clean main

run:
	./main

clean: 
	rm main valgrind-out.txt

debug: main
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=valgrind-out.txt \
	./main