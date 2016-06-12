#include "encoder.hpp"

#include <iostream>

int main(void){

	unsigned char buffer[4] = { 0, 0, 0, 0 };

	utfx::Encoder encoder(utfx::Encoder::Mode::UTF8);

	encoder.Write(U'Φ');

	auto read_count = encoder.Read(buffer, sizeof(buffer));

	for (auto i = 0UL; i < read_count; i++){
		std::cout << buffer[i];
	}
	std::cout << std::endl;

	return 0;
}

