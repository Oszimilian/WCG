#include "Debug.h"
#include <ctime>
#include <sstream>

ocas::Debug* ocas::Debug::instance_ptr = nullptr;


ocas::Debug::Debug() : old_stream() {}

ocas::Debug* ocas::Debug::get() {
	if (instance_ptr == nullptr) {
		instance_ptr = new Debug();
		return instance_ptr;
	} else {
		return instance_ptr;
	}
}


void ocas::Debug::enable_file_logging(std::string path) {
	file = std::make_shared<std::ofstream>(path, std::ofstream::app);
	if (file) {
		old_stream = std::cout.rdbuf();
		std::cout.rdbuf(file.get()->rdbuf());

		time_t now = time(NULL);
		struct tm localTime;
		localtime_s(&localTime, &now);
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);

		std::cout << "---------------------------------------------------------" << std::endl;
		std::cout << "|              STARTED CALCULATION                      |" << std::endl;
		std::cout << "---------------------------------------------------------" << std::endl;
		std::cout << "|              " << buffer << "                      |" << std::endl;
		std::cout << "---------------------------------------------------------" << std::endl;

	}
}

void ocas::Debug::enable_consol_logging() {
	if (old_stream) {
		std::cout.rdbuf(old_stream);
	}
}
