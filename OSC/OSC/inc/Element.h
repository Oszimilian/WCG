#pragma once

#include "Types.h"
#include "Number.h"

namespace ocas {
	class Element {
		public:
			virtual Number process(Number left, Number right) { return Number(); }
			virtual Number get_number() { return Number(); }
			virtual void set_number(Number number) {}
	};
}