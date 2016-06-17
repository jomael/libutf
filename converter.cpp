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

#include "converter.hpp"

namespace utfx {
	Converter::Converter(const Decoder * decoder_, const Encoder * encoder_) noexcept {
		SetDecoder(decoder_);
		SetEncoder(encoder_);
	}
	Decoder Converter::GetDecoder(void) const noexcept {
		return decoder;
	}
	Encoder Converter::GetEncoder(void) const noexcept {
		return encoder;
	}
	void Converter::SetDecoder(const Decoder * decoder_) noexcept {
		decoder = *decoder_;
	}
	void Converter::SetEncoder(const Encoder * encoder_) noexcept {
		encoder = *encoder_;
	}
} /* namespace utfx */

