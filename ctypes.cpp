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

	utfx_decoder_mode_t ToCType(utfx::Decoder::Mode mode) noexcept {
		switch (mode){
			case Decoder::Mode::UTF8:
				return UTFX_DECODER_MODE_UTF8;
			case Decoder::Mode::UTF16_LE:
				return UTFX_DECODER_MODE_UTF16_LE;
			case Decoder::Mode::UTF16_BE:
				return UTFX_DECODER_MODE_UTF16_BE;
			case Decoder::Mode::UTF32_LE:
				return UTFX_DECODER_MODE_UTF32_LE;
			case Decoder::Mode::UTF32_BE:
				return UTFX_DECODER_MODE_UTF32_BE;
			default:
				return UTFX_DECODER_MODE_UNKNOWN;
		}
		/* unreachable */
		return UTFX_DECODER_MODE_UNKNOWN;
	}

	Decoder::Mode ToCPPType(utfx_decoder_mode_t mode) noexcept {
		switch (mode){
			case UTFX_DECODER_MODE_UTF8:
				return Decoder::Mode::UTF8;
			case UTFX_DECODER_MODE_UTF16_LE:
				return Decoder::Mode::UTF16_LE;
			case UTFX_DECODER_MODE_UTF16_BE:
				return Decoder::Mode::UTF16_BE;
			case UTFX_DECODER_MODE_UTF32_LE:
				return Decoder::Mode::UTF32_LE;
			case UTFX_DECODER_MODE_UTF32_BE:
				return Decoder::Mode::UTF32_BE;
			default:
				break;
		}
		/* should be unreachable */
		return Decoder::Mode::UTF8;
	}

	utfx_encoder_mode_t ToCType(utfx::Encoder::Mode mode) noexcept {
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

	utfx_encoder_state_t ToCType(utfx::Encoder::State state) noexcept {
		if (state == utfx::Encoder::State::Reading){
			return UTFX_ENCODER_STATE_READING;
		} else {
			return UTFX_ENCODER_STATE_WRITING;
		}
	}

	Encoder::Mode ToCPPType(utfx_encoder_mode_t mode) noexcept {
		switch (mode){
			case UTFX_ENCODER_MODE_UTF8:
				return Encoder::Mode::UTF8;
			case UTFX_ENCODER_MODE_UTF16_LE:
				return Encoder::Mode::UTF16_LE;
			case UTFX_ENCODER_MODE_UTF16_BE:
				return Encoder::Mode::UTF16_BE;
			case UTFX_ENCODER_MODE_UTF32_LE:
				return Encoder::Mode::UTF32_LE;
			case UTFX_ENCODER_MODE_UTF32_BE:
				return Encoder::Mode::UTF32_BE;
			default:
				break;
		}
		/* should be unreachable */
		return Encoder::Mode::UTF8;
	}

	Encoder::State ToCPPType(utfx_encoder_state_t state) noexcept {
		if (state == UTFX_ENCODER_STATE_READING){
			return Encoder::State::Reading;
		} else {
			return Encoder::State::Writing;
		}
	}

} /* namespace utfx */

