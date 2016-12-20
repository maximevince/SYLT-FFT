all:
	gcc -lasan -Wall -std=c99 -ggdb -m32 -O0 -o example example.c q31in.c q15in.c f32in.c -lm
