#pragma once

#include <iostream>

#include "OSC.h"

namespace ocas {
	std::ostream& operator<<(std::ostream& stream, Number& number);
	std::ostream& operator<<(std::ostream& stream, Vector& vector);
	std::ostream& operator<<(std::ostream& stream, Matrix& matrix);
	std::ostream& operator<<(std::ostream& stream, std::list<std::shared_ptr<Element>>& equation);

	bool is_operand(std::string op);
	std::shared_ptr<Element> get_operator_element(std::string op);
	std::shared_ptr<Element> get_numeric_element(std::string num);
	std::list<std::shared_ptr<Element>> get_Equation_from_Console();
}