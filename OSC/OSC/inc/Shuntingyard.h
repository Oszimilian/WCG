#pragma once

#include <stack>

#include "Element.h"


namespace ocas {
	class Shuntingyard {
		public:
			Shuntingyard();

			std::list<std::shared_ptr<Element>>& import(std::list<std::shared_ptr<Element>>& input_que);
			std::shared_ptr<Element> solve_rpn(std::list<std::shared_ptr<Element>> rpn_notion);


		//private:
			int get_priority(std::shared_ptr<Element>& element);
			int get_id(std::shared_ptr<Element>& element);
			int get_typ_id(std::shared_ptr<Element>& element);

			int stack_get_typ_top();
			void put_stack_top_to_output();
			int stack_get_top_prio();
			void push_operator_stack(std::shared_ptr<Element>& element, int prio);

			std::shared_ptr<Element> solve_equation(std::list<std::shared_ptr<Element>>::iterator it);
			void insert_solution(std::list<std::shared_ptr<Element>>& rpn_notion, std::list<std::shared_ptr<Element>>::iterator it, std::shared_ptr<Element> solution);

			std::list<std::shared_ptr<Element>> output_que;
			std::stack<std::shared_ptr<Element>> operator_stack;

			static const int prio_plus = 0;
			static const int prio_minus = 0;
			static const int prio_mal = 1;
			static const int prio_div = 1;

			static const int id_numeric = 0;
			static const int id_operator = 1;

			static const int id_plus = 0;
			static const int id_minus = 1;
			static const int id_div = 2;
			static const int id_mal = 3;
	};
}