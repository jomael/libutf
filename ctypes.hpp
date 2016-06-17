#ifndef UTFX_CTYPES_HPP
#define UTFX_CTYPES_HPP

#include "encoder.h"
#include "encoder.hpp"

namespace utfx {

	utfx_encoder_mode_t GetCType(utfx::Encoder::Mode mode) noexcept;

	utfx_encoder_state_t GetCType(utfx::Encoder::State state) noexcept;

} /* namespace utfx */

#endif /* UTFX_CTYPES_HPP */

