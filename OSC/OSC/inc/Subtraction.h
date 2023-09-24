#pragma once

#include "Operator.h"

namespace ocas {
	class Subtraction : public Operator {
		public:
			virtual Number process(Number left, Number right);
	};
}