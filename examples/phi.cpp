#include "encoder.hpp"

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

	unsigned char buffer[4] = { 0, 0, 0, 0 };

	auto read_count = encoder.Read(buffer, sizeof(buffer));

	for (auto i = 0UL; i < read_count; i++){
		std::cout << buffer[i];
	}
	std::cout << std::endl;

	return 0;
}

