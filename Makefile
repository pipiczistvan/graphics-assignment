all:
	gcc src\main.c src\window.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o main.exe
 