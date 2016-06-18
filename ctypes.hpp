#ifndef UTFX_CTYPES_HPP
#define UTFX_CTYPES_HPP

#include "decoder.h"
#include "decoder.hpp"

#include "encoder.h"
#include "encoder.hpp"

namespace utfx {

	utfx_decoder_mode_t ToCType(utfx::Decoder::Mode mode) noexcept;

	utfx_decoder_state_t ToCType(utfx::Decoder::State state) noexcept;

	utfx::Decoder::Mode ToCPPType(utfx_decoder_mode_t mode) noexcept;

	utfx::Decoder::State ToCPPType(utfx_decoder_state_t state) noexcept;

	utfx_encoder_mode_t ToCType(utfx::Encoder::Mode mode) noexcept;

	utfx_encoder_state_t ToCType(utfx::Encoder::State state) noexcept;

	utfx::Encoder::Mode ToCPPType(utfx_encoder_mode_t mode) noexcept;

	utfx::Encoder::State ToCPPType(utfx_encoder_state_t state) noexcept;

} /* namespace utfx */

#endif /* UTFX_CTYPES_HPP */

