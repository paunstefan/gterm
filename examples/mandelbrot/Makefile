CXX=g++
CFLAGS=-Wall
OBJ=main.cpp ../../src/gterm.c
INCLUDE=-I../../include

ifndef DEBUG
	CFLAGS+= -Werror -Wpedantic -Wextra
endif

all: mandelbrot

mandelbrot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE) -g -lm

clean:
	rm ./mandelbrot