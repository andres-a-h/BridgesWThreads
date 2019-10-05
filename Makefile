# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

SRCS = traffic.c handlecar.c
OBJS = $(SRCS:.c=.o)
OUTPUT = traffic handlecar

CC = gcc

traffic : $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

.PHONY: test clean

clean:
	rm -f $(OBJS) $(OUTPUT)
