#pragma once

#include "Element.h"

namespace ocas {
	class Operator : public Element{
		public:
			virtual Number process(Number left, Number right) { return Number(); }
	};
}