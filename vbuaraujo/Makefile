

CC=gcc

all: libsched test

libsched: sched.o
	ar crs libsched.a sched.o

sched.o:
	$(CC) -g -O0 -o sched.o -c sched.c -Wall

test:	test.c libsched
	$(CC) -g -O0 -o test test.c -L. -lsched -Wall

clean:
	rm -rf *.a *.o *.x $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
