#pragma once

#include "Operator.h"

namespace ocas {
	class Divider : public Operator {
		public:
			virtual Number process(Number left, Number right);
	};
}