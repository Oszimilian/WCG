#include "Console.h"

#include <iterator>
#include <sstream>
#include <algorithm>

std::ostream& ocas::operator<<(std::ostream& stream, ocas::Number& number) {
	if (number.sign == _MINUS) {
		stream << "-";
	}
	std::for_each(number.left.begin(), number.left.end(), [&](int c) {stream << c << "";  });
	stream << ".";
	std::for_each(number.right.begin(), number.right.end(), [&](int c) {stream << c << "";  });
	if (number.right.size() == 0) stream << 0;
	return stream;
}

std::ostream& ocas::operator<<(std::ostream& stream, ocas::Vector& vector) {
	std::for_each(vector.begin(), vector.end(), [&](int i) {stream << i << " ";  });
	return stream;
}

std::ostream& ocas::operator<<(std::ostream& stream, ocas::Matrix& matrix) {
	std::for_each(matrix.begin(), matrix.end(), [&](ocas::Vector vector) {stream << vector; });
	return stream;
}

std::ostream& ocas::operator<<(std::ostream& stream, std::list<std::shared_ptr<ocas::Element>>& equation) {
	for (const auto& i : equation) {
		ocas::Numeric* numeric = dynamic_cast<ocas::Numeric*>(i.get());
		ocas::Adder* adder = dynamic_cast<ocas::Adder*>(i.get());
		ocas::Subtraction* subtraction = dynamic_cast<ocas::Subtraction*>(i.get());
		ocas::Multiplicator* multiplicator = dynamic_cast<ocas::Multiplicator*>(i.get());
		ocas::Divider* divider = dynamic_cast<ocas::Divider*>(i.get());

		if (numeric != nullptr) {
			auto a = numeric->get_number();
			stream << " " << a << " ";
		}
		else if (adder != nullptr) {
			stream << "+";
		}
		else if (subtraction != nullptr) {
			stream << "-";
		}
		else if (multiplicator != nullptr) {
			stream << "*";
		}
		else if (divider != nullptr) {
			stream << "/";
		}
	}

	return stream;
}

bool ocas::is_operand(std::string op) {
	if (op.size() == 1) {
		switch (op[0]) {
			case '+':
			case '-' :
			case '*':
			case '/':
				return true;

			default: break;
		}
	}
	return false;
}

std::shared_ptr<ocas::Element> ocas::get_operator_element(std::string op) {
	switch (op[0]) {
		case '+' : 
			return std::make_shared<ocas::Adder>();
		case '-':
			return std::make_shared<ocas::Subtraction>();
		case '*':
			return std::make_shared<ocas::Multiplicator>();
		case '/':
			return std::make_shared<ocas::Divider>();
		default: break;
	}
}

std::shared_ptr<ocas::Element> ocas::get_numeric_element(std::string num) {
	ocas::Number number;

	if (num[0] == '-') {
		number.sign = _MINUS;
		num.erase(num.begin(), num.begin() + 1);
	}

	auto it = std::find_if(num.begin(), num.end(), [](char c) {return (c == '.' || c == ',');  });
	std::for_each(num.begin(), it, [&](char c) {number.left.push_back((int)(c - '0'));  });
	it++;
	std::for_each(it, num.end(), [&](char c) {number.right.push_back((int)(c - '0')); });
	
	auto solution = std::make_shared<ocas::Numeric>();
	solution->set_number(number);
	return solution;
}

std::list<std::shared_ptr<ocas::Element>> ocas::get_Equation_from_Console() {
	std::string equation;
	std::cout << "Equation: ";
	std::getline(std::cin, equation);
	std::cout << std::endl;

	std::list<std::shared_ptr<ocas::Element>> solution;

	std::istringstream iss;
	iss.str(equation);
	std::istream_iterator<std::string> it = std::istream_iterator<std::string>(iss);
	std::istream_iterator<std::string> it_end;

	do {		
		if (ocas::is_operand(*it)) {
			solution.push_back(get_operator_element(*it));
		} else {
			solution.push_back(get_numeric_element(*it));
		}
	} while (++it != it_end);
	
	return solution;
}