#include "Shuntingyard.h"
#include "OSC.h"

ocas::Shuntingyard::Shuntingyard() : output_que(), operator_stack() {}

int ocas::Shuntingyard::get_priority(std::shared_ptr<ocas::Element>& element) {
	if (dynamic_cast<ocas::Adder*>(element.get()) != nullptr) {
		return this->prio_plus;
	}
	else if (dynamic_cast<ocas::Divider*>(element.get()) != nullptr) {
		return this->prio_div;
	}
	else if (dynamic_cast<ocas::Multiplicator*>(element.get()) != nullptr) {
		return this->prio_mal;
	}
	else if (dynamic_cast<ocas::Subtraction*>(element.get()) != nullptr) {
		return this->prio_minus;
	}
}

int ocas::Shuntingyard::get_id(std::shared_ptr<ocas::Element>& element) {
	if (dynamic_cast<ocas::Adder*>(element.get()) != nullptr) {
		return this->id_plus;
	}
	else if (dynamic_cast<ocas::Divider*>(element.get()) != nullptr) {
		return this->id_div;
	}
	else if (dynamic_cast<ocas::Multiplicator*>(element.get()) != nullptr) {
		return this->id_mal;
	}
	else if (dynamic_cast<ocas::Subtraction*>(element.get()) != nullptr) {
		return this->id_minus;
	}
}

int ocas::Shuntingyard::get_typ_id(std::shared_ptr<ocas::Element>& element) {
	if (dynamic_cast<ocas::Adder*>(element.get()) != nullptr) {
		return this->id_operator;
	}
	else if (dynamic_cast<ocas::Divider*>(element.get()) != nullptr) {
		return this->id_operator;
	}
	else if (dynamic_cast<ocas::Multiplicator*>(element.get()) != nullptr) {
		return this->id_operator;
	}
	else if (dynamic_cast<ocas::Subtraction*>(element.get()) != nullptr) {
		return this->id_operator;
	}
	else if (dynamic_cast<ocas::Numeric*>(element.get()) != nullptr) {
		return this->id_numeric;
	}
}

int ocas::Shuntingyard::stack_get_typ_top() {
	if (this->operator_stack.size() > 0) {
		return get_id(this->operator_stack.top());
	}
	else {
		return -1;
	}
	 
}

int ocas::Shuntingyard::stack_get_top_prio() {
	if (this->operator_stack.size() > 0) {
		return get_priority(this->operator_stack.top());
	}
	else {
		return -1;
	}
	
}

void ocas::Shuntingyard::put_stack_top_to_output() {
	this->output_que.push_back(this->operator_stack.top());
	int t = get_id(this->operator_stack.top());
	std::string str;
	switch (t) {
	case id_plus: str = "+"; break;
	case id_minus: str = "-"; break;
	case id_div: str = "/"; break;
	case id_mal: str = "*"; break;
	default: break;
	}

	std::cout << "put top of stack to output: " << str << std::endl;
	this->operator_stack.pop();
	
}

void ocas::Shuntingyard::push_operator_stack(std::shared_ptr<ocas::Element>& element, int prio) {
	while (stack_get_top_prio() >= prio) {
		put_stack_top_to_output();
	}
	this->operator_stack.push(element);
	
	int t = get_id(element);
	std::string str;
	switch (t) {
	case id_plus: str = "+"; break;
	case id_minus: str = "-"; break;
	case id_div: str = "/"; break;
	case id_mal: str = "*"; break;
	default: break;
	}

	std::cout << "put operator to stack: " << str << std::endl;
}

std::list<std::shared_ptr<ocas::Element>>& ocas::Shuntingyard::import(std::list<std::shared_ptr<ocas::Element>>& input_que) {

	std::cout << "----------------------------" << std::endl;
	std::cout << "|  SHUNTINGYARD            |" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;

	for (auto& i : input_que) {
		if (get_typ_id(i) == id_numeric) {
			auto a = i.get();
			auto b = a->get_number();
			std::cout << "Put numeric to output: " << b << std::endl;
			this->output_que.push_back(i);
		}
		else {
			switch (get_id(i)) {
			case id_plus:
				push_operator_stack(i, prio_plus);
				break;
			case id_minus:
				push_operator_stack(i, prio_minus);
				break;
			case id_div:
				push_operator_stack(i, prio_div);
				break;
			case id_mal:
				push_operator_stack(i, prio_mal);
				break;
			default: break;
			}
		}
	}

	for (int i = 0; i <= this->operator_stack.size(); i++) {
		put_stack_top_to_output();
	}

	std::cout << "Solution: " << std::endl;
	std::cout << this->output_que << std::endl << std::endl;

	return this->output_que;
}

std::shared_ptr<ocas::Element> ocas::Shuntingyard::solve_equation(std::list<std::shared_ptr<ocas::Element>>::iterator it) {
	auto itr = it;
	itr--;
	auto itl = itr;
	itl--;

	auto result = it->get()->process(itl->get()->get_number(), itr->get()->get_number());
	std::shared_ptr<ocas::Element> solution = std::make_shared<ocas::Numeric>();
	solution->set_number(result);


	return solution;
}

void ocas::Shuntingyard::insert_solution(std::list<std::shared_ptr<ocas::Element>>& rpn_notion, std::list<std::shared_ptr<ocas::Element>>::iterator it, std::shared_ptr<ocas::Element> solution) {
	it--;
	it--;
	rpn_notion.insert(it, solution);
}

std::shared_ptr<ocas::Element> ocas::Shuntingyard::solve_rpn(std::list<std::shared_ptr<ocas::Element>> rpn_notion) {
	while (rpn_notion.size() > 1) {
		auto it = std::find_if(rpn_notion.begin(), rpn_notion.end(), [this](std::shared_ptr<ocas::Element> element) {
			if (this->get_typ_id(element) == id_operator) {
				return true;
			}
			else {
				return false;
			}
		});

		auto solution = solve_equation(it);

		auto m = solution.get()->get_number();

		std::cout << "Solution: " << m << std::endl;

		insert_solution(rpn_notion, it, solution);

		for (int i = 0; i < 3; i++) {
			it = rpn_notion.erase(it);
			it--;
		}

		std::cout << "Step: " << rpn_notion << std::endl << std::endl;
	}

	return *rpn_notion.begin();
}