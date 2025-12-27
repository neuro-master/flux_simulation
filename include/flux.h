#pragma once

typedef struct vector {
	double x, y, z;
} vec;

// Scalar returning functions
double magnitude(vec v);
double dot(vec a, vec b); 

// Vector returning functions
vec add(vec a, vec b); 
vec sub(vec a, vec b); 
vec scalar_multiply(double scale, vec v); 
vec get_unit(vec v);
vec cross(vec a, vec b);

// Get Electric field
vec get_electric_field(vec p, double q, vec q_pos); 
vec get_net_electric_field(vec p, double q_vals[], vec q_pos[], int q_count); 

// Net flux through a triangle - Points specified CCW when outward normal points towards viewer
double get_flux_through_triangle(vec p1, vec p2, vec p3, double q_vals[], vec q_pos[], int q_count, int N); 

