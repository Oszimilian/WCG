#pragma once

#include <list>

#include "Types.h"

namespace ocas {
	class Number {
		public:
			Number() : left(), right(), sign(_PLUS) {}
			std::list<int> left;
			std::list<int> right;
			bool sign;
	};
}