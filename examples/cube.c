#include "flux.h"
#include <stdio.h>

#define e0 8.854e-12

int main() {
	vec vertices[] = { // First to Eighth Quadrant
		{ 1.0,  1.0,  1.0},
		{-1.0,  1.0,  1.0},
		{-1.0, -1.0,  1.0},
		{ 1.0, -1.0,  1.0},
		
		{ 1.0,  1.0, -1.0},
		{-1.0,  1.0, -1.0},
		{-1.0, -1.0, -1.0},
		{ 1.0, -1.0, -1.0}

	};

	unsigned int index_buffer[] = {
		0, 3, 4, // Right Face
		4, 3, 7,

		5, 1, 0, // Top Face
		4, 5, 0,

		0, 1, 2, // Front Face
		0, 2, 3,

		6, 3, 2, // Bottom Face
		6, 7, 3,

		5, 4, 7, // Back Face
		5, 7, 6,

		1, 5, 6, // Left Face
		1, 6, 2
	};

	double q_vals[] = {5.0, -3.0, 7.0};
	vec q_pos[] = { {0.3, -0.7, 0.8}, {-0.25, 0.43, -0.87}, {2.0, 3.0, 4.0} };
	int q_count = 3;

	int N = 1000;

	double net_flux = 0.0;
	for (int i = 0; i < sizeof(index_buffer) / sizeof(int); i += 6) {
		vec p1 = vertices[index_buffer[i + 0]];
		vec p2 = vertices[index_buffer[i + 1]];
		vec p3 = vertices[index_buffer[i + 2]];
		
		vec p4 = vertices[index_buffer[i + 3]];
		vec p5 = vertices[index_buffer[i + 4]];
		vec p6 = vertices[index_buffer[i + 5]];

		double flux1 = get_flux_through_triangle(p1, p2, p3, q_vals, q_pos, q_count, N);
		double flux2 = get_flux_through_triangle(p4, p5, p6, q_vals, q_pos, q_count, N);

		double flux_through_face = flux1 + flux2;
		net_flux += flux_through_face;

		printf("Flux through face %d: %g\n", (i/6)+1, flux_through_face);
	}

	printf("Net flux through cube: %g\n", net_flux);

	double gauss_flux = (q_vals[0] + q_vals[1]) / e0;
	printf("Value of q/e0: %g\n", gauss_flux);

	return 0;
}

