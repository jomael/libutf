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

#ifndef UTFX_DECODER_HPP
#define UTFX_DECODER_HPP

namespace utfx {
	class Decoder {
		public:
			enum class Mode {
				UTF8,
				UTF16_LE,
				UTF16_BE,
				UTF32_LE,
				UTF32_BE };
			enum class State {
				Reading,
				Writing };
		private:
			void * decoder_ptr;
		public:
			Decoder(void);
			Decoder(Mode mode_);
			Mode GetMode(void) const noexcept;
			State GetState(void) const noexcept;
			void SetMode(Mode mode_) noexcept;
			void Write(unsigned char byte);
	}; /* class Decoder */
} /* namespace utfx */

#endif /* UTFX_DECODER_HPP */

