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

#include "ctypes.hpp"

namespace {
	inline utfx_decoder_mode_t get_decoder_mode(const void * converter_ptr) noexcept;
	inline utfx_encoder_mode_t get_encoder_mode(const void * converter_ptr) noexcept;
	inline utfx_converter_state_t get_state(const void * converter_ptr) noexcept;
	inline unsigned int read(void * converter_ptr, void * dst, unsigned int dst_size) noexcept;
	inline void set_decoder_mode(void * converter_ptr, utfx_decoder_mode_t decoder_mode) noexcept;
	inline void set_encoder_mode(void * converter_ptr, utfx_encoder_mode_t encoder_mode) noexcept;
	inline unsigned int write(void * converter_ptr, const void * src, unsigned int src_size) noexcept;
} /* namespace */

namespace utfx {
	Converter::Converter(void) : converter_ptr(0) {
		auto converter = new utfx_converter_t;
		utfx_converter_init(converter);
		converter_ptr = converter;
	}
	Converter::Converter(Decoder::Mode decoder_mode, Encoder::Mode encoder_mode) : Converter() {
		SetDecoderMode(decoder_mode);
		SetEncoderMode(encoder_mode);
	}
	Decoder::Mode Converter::GetDecoderMode(void) const noexcept {
		auto decoder_mode = get_decoder_mode(converter_ptr);
		return ToCPPType(decoder_mode);
	}
	Encoder::Mode Converter::GetEncoderMode(void) const noexcept {
		auto encoder_mode = get_encoder_mode(converter_ptr);
		return ToCPPType(encoder_mode);
	}
	Converter::State Converter::GetState(void) const noexcept {
		auto state = get_state(converter_ptr);
		return ToCPPType(state);
	}
	unsigned int Converter::Read(void * dst, unsigned int dst_size) noexcept {
		return read(converter_ptr, dst, dst_size);
	}
	void Converter::SetDecoderMode(Decoder::Mode decoder_mode) noexcept {
		set_decoder_mode(converter_ptr, ToCType(decoder_mode));
	}
	void Converter::SetEncoderMode(Encoder::Mode encoder_mode) noexcept {
		set_encoder_mode(converter_ptr, ToCType(encoder_mode));
	}
	unsigned int Converter::Write(const void * src, unsigned int src_size) noexcept {
		return write(converter_ptr, src, src_size);
	}
} /* namespace utfx */

namespace {
	inline utfx_decoder_mode_t get_decoder_mode(const void * converter_ptr) noexcept {
		return utfx_converter_get_decoder_mode((const utfx_converter_t *)(converter_ptr));
	}
	inline utfx_encoder_mode_t get_encoder_mode(const void * converter_ptr) noexcept {
		return utfx_converter_get_encoder_mode((const utfx_converter_t *)(converter_ptr));
	}
	inline utfx_converter_state_t get_state(const void * converter_ptr) noexcept {
		return utfx_converter_get_state((const utfx_converter_t *)(converter_ptr));
	}
	inline unsigned int read(void * converter_ptr, void * dst, unsigned int dst_size) noexcept {
		return utfx_converter_read((utfx_converter_t *)(converter_ptr), dst, dst_size);
	}
	inline void set_decoder_mode(void * converter_ptr, utfx_decoder_mode_t decoder_mode) noexcept {
		utfx_converter_set_decoder_mode((utfx_converter_t *)(converter_ptr), decoder_mode);
	}
	inline void set_encoder_mode(void * converter_ptr, utfx_encoder_mode_t encoder_mode) noexcept {
		utfx_converter_set_encoder_mode((utfx_converter_t *)(converter_ptr), encoder_mode);
	}
	inline unsigned int write(void * converter_ptr, const void * src, unsigned int src_size) noexcept {
		return utfx_converter_write((utfx_converter_t *)(converter_ptr), src, src_size);
	}
} /* namespace */

