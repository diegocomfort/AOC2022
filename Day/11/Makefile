CC = clang
FLAGS = -Weverything -ggdb3

all: main

main: main.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

reset: clean main run

run:
	./main

clean: 
	rm main

debug: main
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=valgrind-out.txt \
	./main
