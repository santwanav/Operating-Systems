CC=gcc
IDIR= ./include
CFLAGS=-iquote $(IDIR)
DPES=header.h
OBJ=cat.o

%.o: %.c $(DPES)
	$(CC) -c -o $@ $< $(CFLAGS)
cat: $(OBJ)
	$(CC) -o cat cat.o $(CFLAGS)
