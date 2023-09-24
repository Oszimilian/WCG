#pragma once

#include <tuple>
#include <vector>
#include <list>
#include <memory>


#define _PLUS true
#define _MINUS false

namespace osc {
	typedef std::tuple<std::list<int>, std::list<int>> osc_number;
	typedef std::vector<std::list<int>> osc_matrix;

}

namespace ocas {
	typedef std::vector<std::list<int>> Matrix;
	typedef std::list<int> Vector;
}