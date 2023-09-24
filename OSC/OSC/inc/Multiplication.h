#pragma once

#include "Operator.h"

namespace ocas {
	class Multiplicator : public Operator {
		virtual Number process(Number left, Number right);
	};
}