CFLAGS = -std=c99 -W -Wall -O3 -D_GNU_SOURCE=1 -g
LDFLAGS = -lm -lrt

all: benchmark

test: benchmark
	./benchmark

benchmark: dft.o fft.o benchmark.o stopwatch.o kahan.o

clean:
	rm -f *.o benchmark

