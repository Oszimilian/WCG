#pragma once
//Worksheet Crafter Numeric Area

#include <memory>
#include <vector>

#include "WCA.h"
#include "WCN.h"

namespace wco {
	class WCNA : public WCA{
		public:

		private:
			std::vector<std::shared_ptr<wco::WCN>> numeric_equations;
	};
}