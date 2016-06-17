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

#ifndef UTFX_CONVERTER_HPP
#define UTFX_CONVERTER_HPP

#include "decoder.hpp"
#include "encoder.hpp"

namespace utfx {
	class Converter {
		public:
		private:
			Decoder decoder;
			Encoder encoder;
		public:
			Converter(const Decoder * decoder_, const Encoder * encoder_) noexcept;
			Decoder GetDecoder(void) const noexcept;
			Encoder GetEncoder(void) const noexcept;
			void SetDecoder(const Decoder * decoder) noexcept;
			void SetEncoder(const Encoder * encoder) noexcept;
	}; /* class Converter */
} /* namespace utfx */

#endif /* UTFX_CONVERTER_HPP */

