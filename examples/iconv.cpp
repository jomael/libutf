#include "encoder.hpp"

#include <iostream>

namespace {
	void Iconv(int argc, const char ** argv);
} /* namespace */

int main(int argc, const char ** argv){

	try {
		Iconv(argc, argv);
	} catch (const utfx::Encoder::BadCodeUnit& bad_code_unit){
		std::cerr << argv[0] << ": found bad code unit: " << bad_code_unit.GetCodeUnit() << std::endl;
	}

	return 0;
}

namespace {
	void Iconv(int argc, const char ** argv){
		(void) argc;
		(void) argv;
		utfx::Encoder encoder;
		encoder.Write(0x0110ffff);
	}
} /* namespace */

