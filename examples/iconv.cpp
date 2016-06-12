#include "encoder.hpp"

#include <iostream>

#ifdef _MSC_VER
#pragma warning(disable : 4710)
#pragma warning(disable : 4514)
#endif /* _MSC_VER */

namespace {
	void Iconv(int argc, const char ** argv);
} /* namespace */

int main(int argc, const char ** argv){

	try {
		Iconv(argc, argv);
	} catch (const utfx::Encoder::BadCodeUnit& bad_code_unit){
		std::cerr << argv[0] << ": found bad code unit: " << std::hex << (unsigned int) bad_code_unit.GetCodeUnit() << std::endl;
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

