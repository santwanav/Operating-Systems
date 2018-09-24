CC=gcc
IDIR= ./include
CFLAGS=-iquote $(IDIR)
DPES=header.h
OBJ=cat.o
BINARIES= cat

%.o: %.c $(DPES)
	$(CC) -c -o $@ $< $(CFLAGS)
cat: $(OBJ)
	$(CC) -o cat cat.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(BINARIES) $(OBJ)
