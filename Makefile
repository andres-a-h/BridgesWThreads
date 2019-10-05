# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

SRCS = traffic.c
OBJS = $(SRCS:.c=.o)
OUTPUT = traffic

CC = gcc

traffic : $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

<<<<<<< HEAD
.PHONY: test clean

clean:
	rm -f $(OBJS) $(OUTPUT)
=======
	.PHONY: clean

	clean:
		rm -f $(OBJS) $(OUTPUT)

>>>>>>> 9cc48c822b050cb92f2fb53347a944e33ddb3516
