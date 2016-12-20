all:
	gcc -lasan -Wall -std=c99 -ggdb -m32 -O0 -o example example.c f32in.c -lm
