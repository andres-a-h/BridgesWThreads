# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

SRCS = traffic.c handlecar.c
OBJS = $(SRCS:.c=.o)
OUTPUT = traffic
CFLAGS = -o -g -Wall

CC = gcc

default: traffic

traffic : $(OBJS)
	$(CC) $(CFLAGS) $(OUTPUT) $(OBJS)

traffic.o: traffic.c handlecar.c
	$(CC) $(CFLAGS) -c traffic.c

# create object file handlecar.o for traffic program
handlecar.o : handlecar.c
	$(CC) $(CFLAGS) -c handlecar.c

.PHONY: test clean

clean:
	rm -f $(OBJS) $(OUTPUT)
