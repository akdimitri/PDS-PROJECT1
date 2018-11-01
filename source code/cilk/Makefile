
GCC = gcc
CFLAGS = -O3 -fcilkplus -lcilkrts

CMAIN=qsort

all: qsort-main.o qsort-sequential.o qsort-cilk.o results.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
