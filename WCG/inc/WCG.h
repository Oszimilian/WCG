// WCG.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once
//Worksheet Crafter Generator

#include <iostream>
#include <vector>
#include <memory>

#include "WCA.h"

namespace wco {
	class WCG {
		public:

		private:
			std::vector<std::shared_ptr<wco::WCA>> worksheet_crafter_areas;
	};
}

// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
