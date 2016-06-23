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
	/** A UTF-8, UTF-16 or UTF-32 converter
	 * @ingroup utfx */
	class Converter {
		public:
			/** The state of the converter.
			 * Describes whether it's reading or writing. */
			enum class State {
				/** The converter is reading data. */
				Reading,
				/** The converter is writing data. */
				Writing
			}; /* class State */
		private:
			/** A pointer to the converter structure. */
			void * converter_ptr;
		public:
			Converter(void);
			/** Initializes the converter with a decoding and encoding mode. */
			Converter(Decoder::Mode decoder_mode, Encoder::Mode encoder_mode);
			/** Returns the decoding mode of the converter. */
			Decoder::Mode GetDecoderMode(void) const noexcept;
			/** Returns the encoding mode of the converter. */
			Encoder::Mode GetEncoderMode(void) const noexcept;
			/** Returns the state of the converter. */
			State GetState(void) const noexcept;
			/** Reads encoded data from the converter.
			 * @param dst The address to store the encoded data.
			 * @param dst_size The number of bytes pointed to by @p dst
			 * @returns The number of bytes read.
			 */
			unsigned int Read(void * dst, unsigned int dst_size) noexcept;
			/** Sets the decoder mode.
			 * @param mode The new decoder mode. */
			void SetDecoderMode(Decoder::Mode mode) noexcept;
			/** Sets the encoder mode.
			 * @param mode The new encoder mode. */
			void SetEncoderMode(Encoder::Mode mode) noexcept;
			/** Writes encoded data to the converter.
			 * @param src The address to read the encoded data from.
			 * @param src_size The number of bytes pointed to by @p src
			 * @returns The number of bytes written. */
			unsigned int Write(const void * src, unsigned int src_size) noexcept;
	}; /* class Converter */
} /* namespace utfx */

#endif /* UTFX_CONVERTER_HPP */

