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

namespace {
	void Serialize16LE(char16_t src, void * dst) noexcept;
	void Serialize16BE(char16_t src, void * dst) noexcept;
	void Serialize32LE(char32_t src, void * dst) noexcept;
	void Serialize32BE(char32_t src, void * dst) noexcept;
} /* namespace */

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

		switch (mode){
			case Encoder::Mode::UTF8:
				for (auto i = byte_count_read, j = 0UL; i < unit_count && j < dst_size; i++, j++){
					out8[byte_count_read + i] = dst8[j];
					read_count++;
				}
				break;
			case Encoder::Mode::UTF16_LE:
				Serialize16LE(0, 0);
				break;
			case Encoder::Mode::UTF16_BE:
				Serialize16BE(0, 0);
				break;
			case Encoder::Mode::UTF32_LE:
				Serialize32LE(0, 0);
				break;
			case Encoder::Mode::UTF32_BE:
				Serialize32BE(0, 0);
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
	}

	Encoder& operator << (Encoder& encoder, char32_t input){
		encoder.Write(input);
		return encoder;
	}

} /* namespace utfx */

namespace {
	void Serialize16LE(char16_t src, void * dst) noexcept{
		auto dst8 = (unsigned char *)(dst);
		dst8[0] = (src >> 0x00) & 0xff;
		dst8[1] = (src >> 0x08) & 0xff;
	}
	void Serialize16BE(char16_t src, void * dst) noexcept{
		auto dst8 = (unsigned char *)(dst);
		dst8[0] = (src >> 0x08) & 0xff;
		dst8[1] = (src >> 0x00) & 0xff;
	}
	void Serialize32LE(char32_t src, void * dst) noexcept{
		auto dst8 = (unsigned char *)(dst);
		dst8[0] = (src >> 0x00) & 0xff;
		dst8[1] = (src >> 0x08) & 0xff;
		dst8[2] = (src >> 0x10) & 0xff;
		dst8[3] = (src >> 0x18) & 0xff;
	}
	void Serialize32BE(char32_t src, void * dst) noexcept{
		auto dst8 = (unsigned char *)(dst);
		dst8[0] = (src >> 0x18) & 0xff;
		dst8[1] = (src >> 0x10) & 0xff;
		dst8[2] = (src >> 0x08) & 0xff;
		dst8[3] = (src >> 0x00) & 0xff;
	}
} /* namespace */

