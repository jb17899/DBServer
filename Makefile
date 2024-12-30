flags=-O2 -Wall -std=c2x
ldflags=
all:clean cache22
cache:cache22.o
	cc ${flags} $^ -o $@ ${ldflags}

cache22.o:cache22.c
	cc ${flags} -c $^
clean:
	rm -f *.o cache22