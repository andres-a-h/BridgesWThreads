# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

	SRCS = traffic.c
	OBJS = $(SRCS:.c=.o)
	OUTPUT = traffic

	CC = gcc

	album : $(OBJS)
		$(CC) -o $(OUTPUT) $(OBJS)

	.PHONY: test clean

	clean:
		rm -f $(OBJS) $(OUTPUT)
