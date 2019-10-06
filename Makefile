# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

SRCS = traffic.c handlecar.c
OBJS = $(SRCS:.c=.o)
OUTPUT = traffic
CFLAGS = -g -Wall
CC = gcc

traffic : $(OBJS)
	$(CC) -o $@ $< $(CFLAGS) $(OUTPUT) $(OBJS)

traffic.o: handlecar.h

# create object file handlecar.o for traffic program
handlecar.o : handlecar.h

.PHONY: clean

clean:
	rm -f $(OBJS) $(OUTPUT)
