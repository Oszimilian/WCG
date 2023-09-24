#pragma once

#include "Operator.h"

namespace ocas {
	class Adder : public Operator {
		public:
			virtual Number process(Number left, Number right);
	};
}