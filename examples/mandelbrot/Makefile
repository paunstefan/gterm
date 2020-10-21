CXX=g++
CFLAGS=-Wall
OBJ=main.cpp ../../gterm.c
INCLUDE=-I../../

ifndef DEBUG
	CFLAGS+= -Werror -Wpedantic -Wextra
endif

all: mandelbrot

mandelbrot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE) -g -lm

clean:
	rm ./mandelbrot
