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

#include "encoder.hpp"

namespace utfx {

	Encoder::Error::Error(const char * what) noexcept : std::runtime_error(what) {

	}

	Encoder::Error::~Error(void) noexcept {

	}

	Encoder::BadCodeUnit::BadCodeUnit(char32_t code_unit_) noexcept : Encoder::Error("encoder received bad code unit"), code_unit(code_unit_) {

	}

	Encoder::BadCodeUnit::~BadCodeUnit(void) noexcept {

	}

	char32_t Encoder::BadCodeUnit::GetCodeUnit(void) const noexcept {
		return code_unit;
	}

	Encoder::Encoder(void) noexcept : mode(Encoder::Mode::UTF8), out32(0), unit_count(0) {

	}

	Encoder::Encoder(Encoder::Mode mode_) noexcept : mode(mode_), out32(0), unit_count(0) {

	}

	Encoder::~Encoder(void) noexcept {
	
	}

	Encoder::Mode Encoder::GetMode(void) const noexcept {
		return mode;
	}

	unsigned long int Encoder::Read(void * byte_array_ptr, unsigned long int byte_count) noexcept {

		if (!unit_count){
			return 0;
		}

		auto byte_array = (unsigned char *)(byte_array_ptr);
		auto read_count = 0UL;

		switch (mode){
			case Encoder::Mode::UTF8:
				if (unit_count > byte_count){
					return 0;
				}
				for (auto i = 0UL; i < unit_count; i++){
					byte_array[i] = out8[i];
				}
				read_count = unit_count;
				break;
			default:
				break;
		}

		return read_count;
	}

	void Encoder::SetMode(Encoder::Mode mode_) noexcept {
		mode = mode_;
	}

	void Encoder::Write(char32_t input){
		if (input > 0x0010ffff){
			throw BadCodeUnit(input);
		}
	}

} /* namespace utfx */

