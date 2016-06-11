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

namespace utfx {

	Encoder::Encoder(void) noexcept : mode(Encoder::Mode::UTF8), out32(0) {

	}

	Encoder::~Encoder(void) noexcept {
	
	}

	Encoder::Mode Encoder::GetMode(void) const noexcept {
		return mode;
	}

	void Encoder::SetMode(Encoder::Mode mode_) noexcept {
		mode = mode_;
	}

} /* namespace utfx */

