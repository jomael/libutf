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

#include "ctypes.hpp"

namespace { 

	inline utfx_encoder_mode_t utfx_encoder_get_mode(const void * encoder_ptr) noexcept {
		return utfx_encoder_get_mode((const utfx_encoder_t *)(encoder_ptr));
	}

	inline utfx_encoder_state_t utfx_encoder_get_state(const void * encoder_ptr) noexcept {
		return utfx_encoder_get_state((const utfx_encoder_t *)(encoder_ptr));
	}

	inline unsigned long int utfx_encoder_read(void * encoder_ptr, void * dst, unsigned long int dst_size) noexcept {
		return utfx_encoder_read((utfx_encoder_t *)(encoder_ptr), dst, dst_size);
	}

	inline void utfx_encoder_set_mode(void * encoder_ptr, utfx_encoder_mode_t mode) noexcept {
		return utfx_encoder_set_mode((utfx_encoder_t *)(encoder_ptr), mode);
	}

	inline utfx_error_t utfx_encoder_write(void * encoder_ptr, utf32_t input) noexcept {
		return utfx_encoder_write((utfx_encoder_t *)(encoder_ptr), input);
	}

} /* namespace */

namespace utfx {

	Encoder::Error::Error(const char * what_msg_) noexcept : what_msg(what_msg_) {

	}

	const char * Encoder::Error::What(void) const noexcept {
		return what_msg;
	}

	Encoder::BadCodeUnit::BadCodeUnit(char32_t code_unit_) noexcept : Encoder::Error("encoder received bad code unit"), code_unit(code_unit_) {

	}

	Encoder::BadCodeUnit::~BadCodeUnit(void) noexcept {

	}

	char32_t Encoder::BadCodeUnit::GetCodeUnit(void) const noexcept {
		return code_unit;
	}

	Encoder::Encoder(void) : encoder_ptr(0) {
		auto encoder = new utfx_encoder_t;
		if (encoder){
			utfx_encoder_init(encoder);
		}
		encoder_ptr = encoder;
	}

	Encoder::Encoder(Encoder::Mode mode_) : Encoder() {
		SetMode(mode_);
	}

	Encoder::~Encoder(void) noexcept {
		auto encoder = (utfx_encoder_t *)(encoder_ptr);
		if (encoder){
			delete encoder;
		}
		encoder_ptr = 0;
	}

	Encoder::Mode Encoder::GetMode(void) const noexcept {
		auto mode = utfx_encoder_get_mode(encoder_ptr);
		return ToCPPType(mode);
	}

	Encoder::State Encoder::GetState(void) const noexcept {
		auto state = utfx_encoder_get_state(encoder_ptr);
		return ToCPPType(state);
	}

	unsigned long int Encoder::Read(void * dst, unsigned long int dst_size) noexcept {
		return utfx_encoder_read(encoder_ptr, dst, dst_size);
	}

	void Encoder::SetMode(Encoder::Mode mode_) noexcept {
		utfx_encoder_set_mode(encoder_ptr, ToCType(mode_));
	}

	void Encoder::Write(char32_t input){
		auto error = utfx_encoder_write(encoder_ptr, input);
		switch (error){
			case UTFX_ERROR_NONE:
				break;
			case UTFX_ERROR_INVALID_SEQUENCE:
				throw Encoder::BadCodeUnit(input);
				break;
			default:
				throw Encoder::Error(utfx_strerror(error));
				break;
		}
	}

	Encoder& operator << (Encoder& encoder, char32_t input){
		encoder.Write(input);
		return encoder;
	}

} /* namespace utfx */

