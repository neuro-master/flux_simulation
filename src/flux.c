#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979
#define e0 8.854e-12
#define k (1 / (4*PI*e0))

// Vector and Mathematical Functions

typedef struct vector {
	double x, y, z;
} vec;

double magnitude(vec v) {
	return sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
}

double dot(vec a, vec b) {
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

vec add(vec a, vec b) {
	vec c = { a.x+b.x, a.y+b.y, a.z+b.z };
	return c;
}

vec sub(vec a, vec b) {
	vec c = { a.x-b.x, a.y-b.y, a.z-b.z };
	return c;
}

vec scalar_multiply(double scale, vec v) {
	vec out_v = { scale*v.x, scale*v.y, scale*v.z };
	return out_v;
}

vec get_unit(vec v) {
	double scale_factor = 1.0 / magnitude(v); // Assumes that v is never a zero vector
	return scalar_multiply(scale_factor, v);
}

vec cross(vec a, vec b) { // Returns a cross b
	vec out_v;
	out_v.x = a.y*b.z - a.z*b.y;
	out_v.y = a.z*b.x - a.x*b.z;
	out_v.z = a.x*b.y - a.y*b.x;
	return out_v;
}

// Get Electric field at point p due to charge q located at position 'q_pos'
vec get_electric_field(vec p, double q, vec q_pos) {
	double r = magnitude(sub(p, q_pos));
	double E_mag = (k * q) / (r * r); // Assumes that point and charge never coincide

	vec r_vec_unit = get_unit( sub(p, q_pos) );
	
	vec E_vec = scalar_multiply(E_mag, r_vec_unit);
	return E_vec;
}

vec get_net_electric_field(vec p, double q_vals[], vec q_pos[], int q_count) {
	vec E_vec = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < q_count; i++) {
		E_vec = add(E_vec, get_electric_field(p, q_vals[i], q_pos[i]));
	}
	return E_vec;
}


// Net flux through a triangle - Points specified CCW when outward normal points towards viewer
double get_flux_through_triangle(vec p1, vec p2, vec p3, double q_vals[], vec q_pos[], int q_count, int N) {
	// Get outward normal and other necessary info
	vec a = sub(p2, p1);
	vec b = sub(p3, p1);
	vec da = scalar_multiply( 1.0/N, a);
	vec db = scalar_multiply( 1.0/N, b);

	vec a_cross_b = cross(a, b);
	vec normal = get_unit(a_cross_b);
	double A = 0.5 * magnitude(a_cross_b); // Area of triangle
	double dA_mag = A / (N * N);
	vec dA = scalar_multiply(dA_mag, normal);

	// Calculate flux
	double net_flux = 0.0;
	vec d_a_plus_b = add(da, db);
	vec p_init = add(p1, scalar_multiply( 1.0/3.0, d_a_plus_b));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N-i; j++) {
			vec i_da = scalar_multiply( (double)i, da);
			vec j_db = scalar_multiply( (double)j, db);

			vec P1 = add(add(p_init, i_da), j_db);
			vec E1 = get_net_electric_field(P1, q_vals, q_pos, q_count);
			double flux1 = dot(E1, dA);
			
			double flux2 = 0;
			if (j != N-i-1) { // Add contribution of secondary triangle too (except last row)
				vec P2 = add(P1, scalar_multiply( 1.0/3.0, d_a_plus_b));
				vec E2 = get_net_electric_field(P2, q_vals, q_pos, q_count);
				flux2 = dot(E2, dA);
			}

			double d_flux = flux1 + flux2;
			net_flux += d_flux;
		}
	}

	return net_flux;
}

