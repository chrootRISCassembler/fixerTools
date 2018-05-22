CC = gcc

COMMON_FLAGS = -std=c11 -Wall -Wextra

CFLAGS = $(COMMON_FLAGS) -O2 -march=native 
DCFLAGS = $(COMMON_FLAGS) -fstack-protector-all -O0 -DDEBUG_ -g
LINKFLAGS = $(COMMON_FLAGS) -O2 -march=native
DLINKFLAGS = $(COMMON_FLAGS) -fstack-protector-all -O0 -DDEBUG_ -g

SHELL = /bin/bash

all: collect

collect: src/collect.c
	$(CC) $(CFLAGS) src/collect.c -o collect

clean:
	rm -f *.o
	rm -rf *.dSYM/
