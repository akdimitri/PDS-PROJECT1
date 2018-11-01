
GCC = gcc
CFLAGS = -O3 -fopenmp

CMAIN=qsort

all: qsort-main.o qsort-sequential.o qsort-openmp.o results.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
