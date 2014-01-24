CFLAGS = -std=c99 -W -Wall -O3 -D_GNU_SOURCE=1 -g
LDFLAGS = -lm -lrt

all: benchmark

test: benchmark
	./benchmark 4096

benchmark: dft.o fft.o benchmark.o stopwatch.o kahan.o

blah: benchmark
	for (( i = 2; i < 15; i++)) ; do ./benchmark $$((2**i)) ; done >> blah.dat

clean:
	rm -f *.o benchmark

