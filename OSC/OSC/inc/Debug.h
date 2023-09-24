#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

namespace ocas {
	class Debug {
		private:
			Debug();
			static Debug* instance_ptr;

			std::shared_ptr<std::ofstream> file;
			std::streambuf* old_stream;

		public:
			static Debug* get();

			void enable_file_logging(std::string path);
			void enable_consol_logging();
	};
}

