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
			enum class State {
				Reading,
				Writing
			}; /* class State */
		private:
			void * converter_ptr;
		public:
			Converter(void);
			Converter(Decoder::Mode decoder_mode, Encoder::Mode encoder_mode);
			Decoder::Mode GetDecoderMode(void) const noexcept;
			Encoder::Mode GetEncoderMode(void) const noexcept;
			State GetState(void) const noexcept;
			unsigned int Read(void * dst, unsigned int dst_size) noexcept;
			void SetDecoderMode(Decoder::Mode mode) noexcept;
			void SetEncoderMode(Encoder::Mode mode) noexcept;
			unsigned int Write(const void * src, unsigned int src_size) noexcept;
	}; /* class Converter */
} /* namespace utfx */

#endif /* UTFX_CONVERTER_HPP */

