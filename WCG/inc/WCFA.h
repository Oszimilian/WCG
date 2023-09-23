#pragma once
//Worksheet Crafter Form Area

#include "WCA.h"
#include "WCF.h"

#include <vector>
#include <memory>

namespace wco {
	class WCFA : public WCA {
		public:

		private:
			std::vector<std::shared_ptr<wco::WCF>> form_equations;
	};
}