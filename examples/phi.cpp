#include "encoder.hpp"
#include "stl.hpp"

#include <iostream>

#ifdef _MSC_VER
#pragma warning(disable : 4710)
#pragma warning(disable : 4514)
#endif /* _MSC_VER */

int main(void){

	utfx::Encoder encoder;

#ifdef _MSC_VER
	encoder << 0x03a6;
#else /* _MSC_VER */
	encoder << U'Φ';
#endif /* _MSC_VER */

	std::cout << encoder << std::endl;

	return 0;
}

