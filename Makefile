# Makefile for Bridge W/ Threads program
# Andres Hernandez, Dartmouth College, Fall 2019

.SUFFIXES: .c

LINK_TARGET = test
OBJS = traffic.o handlecar.o
REBUILDABLES = $(OBJS) $(LINK_TARGET)
LIBS = -pthread

.PHONY: clean all
	
clean:
    rm -f $(REBUILDABLES)
    echo Clean done

all: $(LINK_TARGET)
    echo All done

$(LINK_TARGET) : $(OBJS)
    gcc -g -o $@ $^ $(LIBS)

$.o : $.c
    gcc -g -o $@ -c $<

Main.o : ThreadFunction.h
ThreadFunction.o : ThreadFunction.h
