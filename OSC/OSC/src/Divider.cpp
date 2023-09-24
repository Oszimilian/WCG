#include "Divider.h"
#include "Engine.h"
#include "Console.h"

#include <iostream>

using namespace ocas;

Number Divider::process(Number left, Number right) {
	ocas::Number solution;

	std::cout << "----------------------------" << std::endl;
	std::cout << "|  DIVIDE                  |" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;

	std::cout << "Dividiere: " << std::endl;
	std::cout << left << " / " << right << std::endl << std::endl;

	left = ocas::cleanup_number(left);
	right = ocas::cleanup_number(right);

	std::cout << "After cleanup" << std::endl;
	std::cout << left << " / " << std::endl << std::endl;

	int left_decimal_places = ocas::get_decimal_places(left);
	int right_decimal_places = ocas::get_decimal_places(right);

	if (left_decimal_places > right_decimal_places) {
		right = append_zeros_right(right, left_decimal_places - right_decimal_places);
	}
	else {
		left = append_zeros_right(left, right_decimal_places - left_decimal_places);
	}

	std::cout << "After appending zeros right to get rid of dezimal places" << std::endl;
	std::cout << left << " / " << std::endl << std::endl;

	ocas::Vector left_list = ocas::make_vector(left);
	ocas::Vector right_list = ocas::make_vector(right);

	std::cout << "After creating two vectors containing the integer value" << std::endl;
	std::cout << left_list << " / " << right_list << std::endl << std::endl;

	int left_value = ocas::get_value(left_list);
	int right_value = ocas::get_value(right_list);

	std::cout << "After creating real integer for dividing algo" << std::endl;
	std::cout << left_value << " / " << right_value << std::endl << std::endl;

	std::cout << "Dividing:" << std::endl;
	int count = 0;
	do {
		if (count > 0) {
			solution.right.push_back(left_value / right_value);
			std::cout << left_value / right_value << std::endl;
			
		} else {
			solution.left = ocas::make_vector(left_value / right_value);
			std::cout << solution.left << "." << std::endl;
		}

		left_value %= right_value;

		if (left_value == 0 || count++ == 20) break;

		left_value *= 10;

		while (left_value < right_value) {
			left_value *= 10;
			solution.right.push_back(0);
			std::cout << "0" << std::endl;
		}
	} while (true);

	std::cout << std::endl << std::endl;

	std::cout << "Solution: " << std::endl;
	std::cout << left << " / " << right << " = " << solution << std::endl << std::endl;

	return solution;
}