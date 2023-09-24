#pragma once

#include <iostream>

#include "Number.h"

namespace ocas {
	std::list<int> cleanup_from_right(std::list<int> list);
	std::list<int> cleanup_from_left(std::list<int> list);
	Number cleanup_number(Number number);

	size_t get_decimal_places(Number number);
	size_t get_integer_places(Number number);

	Number append_zeros_left(Number number, int i);
	Number append_zeros_right(Number number, int i);

	Matrix make_multiply_matrix(Number left, Number right);
	Matrix make_addition_matrix(Number left, Number right);
	Vector add_matrix(Matrix matrix);
	Vector sub_matrix(Matrix matrix);
	size_t matrix_len(Matrix matrix);
	Matrix zero_matrix(Matrix matrix);

	int get_value(Vector vector);
	int get_value(Number number);

	Vector make_vector(Number number);
	Vector make_vector(int number);

	Number make_number(Vector vector, int decimal_places);

	bool is_left_more_than_right(Number left, Number right);

}