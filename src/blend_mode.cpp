// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "jhoyt/media-framework/blend_mode.hpp"

namespace jhoyt::mf
{

    blend_mode blend_mode::compose_custom(blend_factor src_color_factor,
                                          blend_factor dst_color_factor,
                                          blend_operation color_operation,
                                          blend_factor src_alpha_factor,
                                          blend_factor dst_alpha_factor,
                                          blend_operation alpha_operation)
    {
        auto bm = blend_mode{};
        bm.value_ = SDL_ComposeCustomBlendMode(static_cast<SDL_BlendFactor>(src_color_factor),
                                               static_cast<SDL_BlendFactor>(dst_color_factor),
                                               static_cast<SDL_BlendOperation>(color_operation),
                                               static_cast<SDL_BlendFactor>(src_alpha_factor),
                                               static_cast<SDL_BlendFactor>(dst_alpha_factor),
                                               static_cast<SDL_BlendOperation>(alpha_operation));
        return bm;
    }

} // namespace jhoyt::mf