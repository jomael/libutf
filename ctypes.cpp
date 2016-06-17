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

#include "ctypes.hpp"

namespace utfx {

	utfx_encoder_mode_t GetCType(utfx::Encoder::Mode mode) noexcept {
		switch (mode){
			case Encoder::Mode::UTF8:
				return UTFX_ENCODER_MODE_UTF8;
			case Encoder::Mode::UTF16_LE:
				return UTFX_ENCODER_MODE_UTF16_LE;
			case Encoder::Mode::UTF16_BE:
				return UTFX_ENCODER_MODE_UTF16_BE;
			case Encoder::Mode::UTF32_LE:
				return UTFX_ENCODER_MODE_UTF32_LE;
			case Encoder::Mode::UTF32_BE:
				return UTFX_ENCODER_MODE_UTF32_BE;
			default:
				return UTFX_ENCODER_MODE_UNKNOWN;
		}
		/* unreachable */
		return UTFX_ENCODER_MODE_UNKNOWN;
	}

	utfx_encoder_state_t GetCType(utfx::Encoder::State state) noexcept {
		if (state == utfx::Encoder::State::Reading){
			return UTFX_ENCODER_STATE_READING;
		} else {
			return UTFX_ENCODER_STATE_WRITING;
		}
	}

} /* namespace utfx */

