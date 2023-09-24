#include "Subtraction.h"
#include "Engine.h"
#include "Console.h"

#include <iostream>

using namespace ocas;

Number Subtraction::process(Number left, Number right) {
	ocas::Number solution;

	std::cout << "----------------------------" << std::endl;
	std::cout << "|  SUBTRACTION             |" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;

	std::cout << "Subtract: " << std::endl;
	std::cout << left << " - " << right << std::endl << std::endl;

	left = ocas::cleanup_number(left);
	right = ocas::cleanup_number(right);

	std::cout << "After cleanup" << std::endl;
	std::cout << left << " - " << std::endl << std::endl;

	if (ocas::is_left_more_than_right(left, right) == false) {
		auto back = left;
		left = right;
		right = back;
		solution.sign = _MINUS;
	}

	size_t left_decimal_places = ocas::get_decimal_places(left);
	size_t right_decimal_places = ocas::get_decimal_places(right);
	size_t left_integer_places = ocas::get_integer_places(left);
	size_t right_integer_places = ocas::get_integer_places(right);

	if (left_integer_places > right_integer_places) {
		right = ocas::append_zeros_left(right, left_integer_places - right_integer_places);
	}
	else {
		left = ocas::append_zeros_left(left, right_integer_places - left_integer_places);
	}

	if (left_decimal_places > right_decimal_places) {
		right = ocas::append_zeros_right(right, left_decimal_places - right_decimal_places);
	}
	else {
		left = ocas::append_zeros_right(left, right_decimal_places - left_decimal_places);
	}

	std::cout << "After appending zeros right and left for making matrix" << std::endl;
	std::cout << left << " - " << std::endl << std::endl;

	std::size_t decimal_places = (left_decimal_places > right_decimal_places) ? left_decimal_places : right_decimal_places;

	ocas::Matrix matrix = ocas::make_addition_matrix(left, right);

	std::cout << "After building matrix" << std::endl;
	std::cout << matrix << std::endl << std::endl;

	ocas::Vector vector = ocas::sub_matrix(matrix);

	std::cout << "After creating vector out of matrix" << std::endl;
	std::cout << vector << std::endl << std::endl;

	solution = ocas::make_number(vector, decimal_places);

	std::cout << "Solution: " << std::endl;
	std::cout << left << " - " << right << " = " << solution << std::endl << std::endl;

	return solution;
}