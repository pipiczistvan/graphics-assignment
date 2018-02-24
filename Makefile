CC=gcc
LIBS=-lSOIL -lglut32 -lopengl32 -lglu32 -lm
CFLAGS=-Wall

SRC=$(wildcard src/**/**/*.c) $(wildcard src/**/*.c) $(wildcard src/*.c)
OUTPUT=main.exe

all:
	$(CC) $(SRC) -o $(OUTPUT) $(CFLAGS) $(LIBS)
