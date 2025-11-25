// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_blendmode.h>

namespace jhoyt::mf
{

    enum class blend_mode_type : uint32_t
    {
        none = SDL_BLENDMODE_NONE,
        blend = SDL_BLENDMODE_BLEND,
        blend_premultiplied = SDL_BLENDMODE_BLEND_PREMULTIPLIED,
        add = SDL_BLENDMODE_ADD,
        add_premultiplied = SDL_BLENDMODE_ADD_PREMULTIPLIED,
        mod = SDL_BLENDMODE_MOD,
        mul = SDL_BLENDMODE_MUL,
        invalid = SDL_BLENDMODE_INVALID
    };

    enum class blend_operation
    {
        add = SDL_BLENDOPERATION_ADD,
        subtract = SDL_BLENDOPERATION_SUBTRACT,
        rev_subtract = SDL_BLENDOPERATION_REV_SUBTRACT,
        minimum = SDL_BLENDOPERATION_MINIMUM,
        maximum = SDL_BLENDOPERATION_MAXIMUM
    };

    enum class blend_factor
    {
        zero = SDL_BLENDFACTOR_ZERO,
        one = SDL_BLENDFACTOR_ONE,
        src_color = SDL_BLENDFACTOR_SRC_COLOR,
        one_minus_src_color = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
        src_alpha = SDL_BLENDFACTOR_SRC_ALPHA,
        one_minus_src_alpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
        dst_color = SDL_BLENDFACTOR_DST_COLOR,
        one_minus_dst_color = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
        dst_alpha = SDL_BLENDFACTOR_DST_ALPHA,
        one_minus_dst_alpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
    };

    class blend_mode final
    {
    public:
        static blend_mode compose_custom(blend_factor src_color_factor,
                                         blend_factor dst_color_factor,
                                         blend_operation color_operation,
                                         blend_factor src_alpha_factor,
                                         blend_factor dst_alpha_factor,
                                         blend_operation alpha_operation);

        blend_mode() = default;

        blend_mode(blend_mode_type type) : value_(static_cast<uint32_t>(type))
        {
        }

        explicit blend_mode(const uint32_t value) : value_(value)
        {
        }

        auto get_value() const
        {
            return value_;
        }

    private:
        uint32_t value_ = static_cast<uint32_t>(blend_mode_type::none);
    };
} // namespace jhoyt::mf