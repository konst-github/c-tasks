CC=gcc
CFLAGS=-Wall -std=c11

DIR_LOWERCASE=lowercase
DIR_MOST_COMMON=most_common

task_lowercase:
	$(MAKE) -C $(DIR_LOWERCASE)

task_most_common:
	$(MAKE) -C $(DIR_MOST_COMMON)

clean:
	cd $(DIR_LOWERCASE) && rm -rf *.o
	cd $(DIR_MOST_COMMON) && rm -rf *.o

all: task_most_common task_lowercase clean
