#pragma once

#include "Element.h"

namespace ocas {
	class Numeric : public Element {
		public:
			Numeric();
			virtual Number get_number();
			virtual void set_number(Number number);
		private:
			Number number;

	};
}