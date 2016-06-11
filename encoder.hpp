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

#ifndef UTFX_ENCODER_HPP
#define UTFX_ENCODER_HPP

#include <stdexcept>

namespace utfx {

	/** A UTF-8, UTF-16 or UTF-32 encoder.
	 * @ingroup utfx_encoder
	 * */

	class Encoder {
		public:
			class Error : public std::runtime_error {
				public:
					Error(void) noexcept;
					virtual ~Error(void) noexcept;
					virtual const char * what(void) const noexcept;
			}; /* class Error */
			class BadCodeUnit : public Error {
				public:
					BadCodeUnit(void) noexcept;
					virtual ~BadCodeUnit(void) noexcept;
					char32_t GetCodeUnit(void) const noexcept;
			}; /* class BadCodeUnit */
			enum class Mode {
				UTF8,
				UTF16_LE, UTF16_BE,
				UTF32_LE, UTF32_BE };
		private:
			Mode mode;
			union {
				char out8;
				char16_t out16;
				char32_t out32; };
		public:
			Encoder(void) noexcept;
			~Encoder(void) noexcept;
			Encoder::Mode GetMode(void) const noexcept;
			void SetMode(Encoder::Mode mode) noexcept;
			void Write32(char32_t input);
	}; /* class Encoder */

} /* namespace utfx */

#endif /* UTFX_ENCODER_HPP */

