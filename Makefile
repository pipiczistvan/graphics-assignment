CC=gcc
LIBS=-lSOIL -lglut32 -lopengl32 -lglu32 -lm
CFLAGS=-Wall -Wextra -Wpedantic

SRC=$(wildcard code/src/**/*.c) $(wildcard code/src/*.c)
OUTPUT=main.exe

all:
	$(CC) -Icode/include/ $(SRC) -o $(OUTPUT) $(LIBS)
