// OSC.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include <memory>

#include "OSC.h"
#include "Shuntingyard.h"
#include "Debug.h"

using namespace std;

int main()
{
	auto debug = ocas::Debug::get();
	

	auto equation = ocas::get_Equation_from_Console();

	debug->enable_file_logging("log.txt");

	std::cout << "----------------------------" << std::endl;
	std::cout << "|  INPUT                   |" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;
	std::cout << equation << std::endl;

	ocas::Shuntingyard sy;
	auto ro = sy.import(equation);

	std::cout << ro << std::endl << std::endl;

	// 5.0 + 10.0 / 2.0 - 5.0 * 2.0
	auto ret = sy.solve_rpn(ro);
	auto solution = ret.get()->get_number();

	debug->enable_consol_logging();

	std::cout << "----------------------------" << std::endl;
	std::cout << "|  SOLUTION                |" << std::endl;
	std::cout << "----------------------------" << std::endl << std::endl;
	std::cout << "=> " << solution << std::endl;
	debug->enable_consol_logging();
	std::cout << "=> " << solution << std::endl;

	return 0;
}
