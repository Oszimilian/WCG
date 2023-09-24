#include <algorithm>
#include <cmath>

#include "Engine.h"



std::list<int> ocas::cleanup_from_left(std::list<int> list) {
	std::list<int> solution;
	auto it = std::find_if(list.begin(), list.end(), [](int i) {return (i != 0); });
	std::copy(it, list.end(), std::back_inserter(solution));
	return solution;
}

std::list<int> ocas::cleanup_from_right(std::list<int> list) {
	std::list<int> solution;
	auto it = std::find_if(list.rbegin(), list.rend(), [](int i) {return i != 0;  });
	std::copy(list.begin(), it.base(), std::back_inserter(solution));
	return solution;
}

ocas::Number ocas::cleanup_number(Number number) {
	ocas::Number solution;
	solution.left = ocas::cleanup_from_left(number.left);
	solution.right = ocas::cleanup_from_right(number.right);
	solution.sign = number.sign;
	return solution;
}

size_t ocas::get_decimal_places(Number number) {
	return number.right.size();
}

size_t ocas::get_integer_places(Number number) {
	return number.left.size();
}

ocas::Number ocas::append_zeros_left(ocas::Number number, int i) {
	for (int j = 0; j < i; j++) number.left.push_front(0);
	return number;
}

ocas::Number ocas::append_zeros_right(ocas::Number number, int i) {
	for (int j = 0; j < i; j++) number.right.push_back(0);
	return number;
}

ocas::Vector ocas::make_vector(ocas::Number number) {
	ocas::Vector solution;
	std::for_each(number.left.begin(), number.left.end(), [&](int i) {solution.push_back(i);  });
	std::for_each(number.right.begin(), number.right.end(), [&](int i) {solution.push_back(i);  });
	return solution;
}

int ocas::get_value(ocas::Number number) {
	ocas::Vector vector;
	
	number = ocas::cleanup_number(number);

	for (auto i : number.left) vector.push_back(i);
	for (auto i : number.right) vector.push_back(i);

	return get_value(vector);
}

int ocas::get_value(ocas::Vector vector) {
	int solution = 0;
	int count = 0;
	std::for_each(vector.rbegin(), vector.rend(), [&](int i) {
		solution += i * std::pow(10, count++);
	});
	return solution;
}

ocas::Vector ocas::make_vector(int number) {
	ocas::Vector solution;
	if (number == 0) solution.push_back(0);
	while (number > 0) {
		solution.push_front(number % 10);
		number /= 10;
	}
	return solution;
}

ocas::Matrix ocas::zero_matrix(ocas::Matrix matrix) {
	int max_len = 0;
	for (const auto& i : matrix) {
		max_len = (max_len < i.size()) ? i.size() : max_len;
	}
		
	for (auto& i : matrix) {
		int dif = max_len - i.size();
		for (int j = 0; j < dif; j++) {
			i.push_front(0);
		}
	}

	return matrix;
}

ocas::Matrix ocas::make_multiply_matrix(ocas::Number left, ocas::Number right) {
	ocas::Matrix solution;

	int left_value = get_value(left);
	ocas::Vector vector = make_vector(right);

	int i = 0;
	for (auto it = vector.rbegin(); it != vector.rend(); it++, i++) {
		int val = left_value * (*it) * std::pow(10, i);
		solution.push_back(make_vector(val));
	}

	return zero_matrix(solution);
}

ocas::Matrix ocas::make_addition_matrix(ocas::Number left, ocas::Number right) {
	ocas::Matrix solution;
	solution.push_back(ocas::make_vector(left));
	solution.push_back(ocas::make_vector(right));
	return zero_matrix(solution);
}


std::size_t ocas::matrix_len(ocas::Matrix matrix) {
	return matrix.at(0).size();
}

ocas::Vector ocas::add_matrix(ocas::Matrix matrix) {
	ocas::Vector solution(matrix_len(matrix));
	for (const auto& i : matrix) {
		auto itl = solution.begin();
		for (auto itm = i.begin(); itm != i.end() && itl != solution.end(); itm++, itl++) {
			*itl += *itm;
		}
	}

	for (auto it = solution.rbegin(); it != solution.rend(); it++) {
		ocas::Vector::reverse_iterator next_it = it;
		next_it++;

		if (next_it != solution.rend()) {
			*next_it += *it / 10;
		} else {
			if ((*it / 10) > 0) {
				solution.push_front(*it / 10);
			}
		}

		*it = *it % 10;
	}

	return solution;
}

ocas::Number ocas::make_number(ocas::Vector vector, int decimal_places) {
	ocas::Number solution;

	auto it = vector.rbegin();
	int i = 0;

	for (; i < decimal_places && it != vector.rend(); it++, i++) solution.right.push_front(*it);
	for (; i < decimal_places; i++) solution.right.push_front(0);

	if (it != vector.rend()) {
		for (; it != vector.rend(); it++) {
			solution.left.push_front(*it);
		}
	} else {
		solution.left.push_front(0);
	}

	return solution;
}

bool ocas::is_left_more_than_right(ocas::Number left, ocas::Number right) {
	if (ocas::get_value(left.left) < ocas::get_value(right.left)) return false;

	auto itl = left.right.begin();
	auto itr = right.right.begin();

	for (; itl != left.right.end() && itr != right.right.end(); itl++, itr++) {
		if (*itl < *itr) return false;
	}

	if (itl == left.right.end() && itr != right.right.end()) {
		return false;
	}
	
	return true;
}

ocas::Vector ocas::sub_matrix(ocas::Matrix matrix) {
	ocas::Vector solution;

	ocas::Vector left = matrix[0];
	ocas::Vector right = matrix[1];

	auto itl = left.rbegin();
	auto itr = right.rbegin();

	for (; itl != left.rend() && itr != right.rend(); itl++, itr++) {
		auto next_itl = itl;
		next_itl++;

		if (*itl >= *itr) {
			solution.push_front(*itl - *itr);
		}
		else {
			if (next_itl != left.rend()) {
				(*next_itl)--;
				(*itl) += 10;
				solution.push_front(*itl - *itr);
			}
			else {
				solution.push_front(*itl - *itr);
			}
		}
	}

	return solution;
}