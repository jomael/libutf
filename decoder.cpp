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

#include "decoder.hpp"

#include "ctypes.hpp"

namespace {
	inline auto get_mode(void * decoder_ptr){
		return utfx_decoder_get_mode((utfx_decoder_t *)(decoder_ptr));
	}
	inline auto get_state(void * decoder_ptr){
		return utfx_decoder_get_state((utfx_decoder_t *)(decoder_ptr));
	}
	inline auto set_mode(void * decoder_ptr, utfx_decoder_mode_t mode){
		utfx_decoder_set_mode((utfx_decoder_t *)(decoder_ptr), mode);
	}
} /* namespace */

namespace utfx {
	Decoder::Decoder(void) : decoder_ptr(0) {
		decoder_ptr = new utfx_decoder_t;
	}
	Decoder::Decoder(Mode mode_) : Decoder() {
		SetMode(mode_);
	}
	Decoder::Mode Decoder::GetMode(void) const noexcept {
		auto mode = get_mode(decoder_ptr);
		return ToCPPType(mode);
	}
	Decoder::State Decoder::GetState(void) const noexcept {
		auto c_state = get_state(decoder_ptr);
		return ToCPPType(c_state);
	}
	void Decoder::SetMode(Mode mode) noexcept {
		auto c_mode = ToCType(mode);
		set_mode(decoder_ptr, c_mode);
	}
} /* namespace utfx */

