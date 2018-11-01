
GCC = gcc
CFLAGS = -pthread -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o qsort-pthreads.o results.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
