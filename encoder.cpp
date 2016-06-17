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

#include "utf8.h"
#include "utf16.h"
#include "utf32.h"

#ifdef _MSC_VER
#pragma warning(disable : 4514)
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

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

	Encoder::Encoder(void) noexcept : mode(Encoder::Mode::UTF8), state(Encoder::State::Reading), unit_count(0) {
		byte_count_read = 0;
		for (auto i = 0UL; i < sizeof(out32) / sizeof(out32[0]); i++){
			out32[i] = 0;
		}
	}

	Encoder::Encoder(Encoder::Mode mode_) noexcept : mode(mode_), state(Encoder::State::Reading), unit_count(0) {
		byte_count_read = 0;
		for (auto i = 0UL; i < sizeof(out32) / sizeof(out32[0]); i++){
			out32[i] = 0;
		}
	}

	Encoder::~Encoder(void) noexcept {
	
	}

	Encoder::Mode Encoder::GetMode(void) const noexcept {
		return mode;
	}

	Encoder::State Encoder::GetState(void) const noexcept {
		return state;
	}

	unsigned long int Encoder::Read(void * dst, unsigned long int dst_size) noexcept {

		auto read_count = 0UL;

		auto dst8 = (unsigned char*)(dst);

		auto src_size = unit_count;
		auto src_start = byte_count_read;

		switch (mode){
			case Encoder::Mode::UTF8:
				for (auto i = src_start, j = 0UL; i < src_size && j < dst_size; i++, j++){
					dst8[j] = out8[i];
					read_count++;
				}
				break;
			case Encoder::Mode::UTF16_LE:
				for (auto i = src_start, j = 0UL; i < src_size && j < dst_size; i++, j++){
					if (j % 2 == 0){
						dst8[j] = out16[i] & 0xff;
					} else {
						dst8[j] = (out16[i] >> 0x08) & 0xff;
					}
					read_count++;
				}
				break;
			case Encoder::Mode::UTF16_BE:
				for (auto i = src_start, j = 0UL; i < src_size && j < dst_size; i++, j++){
					if (j % 2 == 0){
						dst8[j] = (out16[i] >> 0x08) & 0xff;
					} else {
						dst8[j] = out16[i] & 0xff;
					}
					read_count++;
				}
				break;
			case Encoder::Mode::UTF32_LE:
				for (auto i = src_start, j = 0UL; i < src_size && j < dst_size; i++, j++){
					auto k = j % 4;
					if (k == 0){
						dst8[j] = out16[i] & 0xff;
					} else if (k == 1){
						dst8[j] = (out16[i] >> 0x08) & 0xff;
					} else if (k == 2){
						dst8[j] = (out16[i] >> 0x10) & 0xff;
					} else if (k == 3){
						dst8[j] = (out16[i] >> 0x18) & 0xff;
					}
					read_count++;
				}
				break;
			case Encoder::Mode::UTF32_BE:
				for (auto i = src_start, j = 0UL; i < src_size && j < dst_size; i++, j++){
					auto k = j % 4;
					if (k == 0){
						dst8[j] = (out16[i] >> 0x18) & 0xff;
					} else if (k == 1){
						dst8[j] = (out16[i] >> 0x10) & 0xff;
					} else if (k == 2){
						dst8[j] = (out16[i] >> 0x08) & 0xff;
					} else if (k == 3){
						dst8[j] = out16[i] & 0xff;
					}
					read_count++;
				}
				break;
			default:
				break;
		}

		byte_count_read += read_count;

		return read_count;
	}

	void Encoder::SetMode(Encoder::Mode mode_) noexcept {
		mode = mode_;
	}

	void Encoder::Write(char32_t input){
		if (input > utf32_max){
			throw BadCodeUnit(input);
		}

		switch (mode){
			case Encoder::Mode::UTF8:
				unit_count = utf8_encode(out8, input);
				break;
			case Encoder::Mode::UTF16_LE:
			case Encoder::Mode::UTF16_BE:
				unit_count = utf16_encode(input, (utf16_t*)(out16));
				break;
			case Encoder::Mode::UTF32_LE:
			case Encoder::Mode::UTF32_BE:
				out32[0] = (utf32_t)(input);
				unit_count = 1;
				break;
		}

		byte_count_read = 0;
	}

	Encoder& operator << (Encoder& encoder, char32_t input){
		encoder.Write(input);
		return encoder;
	}

} /* namespace utfx */

