/*
 *    This file is part of Utfx.
 *
 *    Utfx is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utfx is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utfx.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stl.hpp"

std::ostream& operator << (std::ostream& output, utfx::Encoder& encoder){

	union {
		char out8[4];
		char16_t out16[2];
		char32_t out32[1];
	};

	auto read_count = 0UL;

	auto mode = encoder.GetMode();

	switch (mode){
		case utfx::Encoder::Mode::UTF8:
			read_count = encoder.Read(out8, 4);
			for (auto i = 0UL; i < read_count; i++){
				std::cout << out8[i];
			}
			break;
		case utfx::Encoder::Mode::UTF16_LE:
		case utfx::Encoder::Mode::UTF16_BE:
			read_count = encoder.Read(out16, 2);
			for (auto i = 0UL; i < read_count / 2; i++){
				std::cout << out16[i];
			}
			break;
		case utfx::Encoder::Mode::UTF32_LE:
		case utfx::Encoder::Mode::UTF32_BE:
			read_count = encoder.Read(out32, 1);
			for (auto i = 0UL; i < read_count / 4; i++){
				std::cout << out32[i];
			}
			break;
		default:
			break;
	}

	return output;
}

