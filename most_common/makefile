CC=gcc
CFLAGS=-Wall -std=c11

task: main.o generator.o
	$(CC) -o most_common main.o generator.o

clean:
	rm -f task main.o generator.o

all: task clean
