all: compile_cube compile_cylinder

compile_cube:
	gcc examples/cube.c src/flux.c -I include -lm -O3 -o bin/cube

compile_cylinder:
	gcc examples/cylinder.c src/flux.c -I include -lm -O3 -o bin/cylinder

