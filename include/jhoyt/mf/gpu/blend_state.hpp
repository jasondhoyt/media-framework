// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "blend_factor.hpp"
#include "blend_op.hpp"
#include "color_component.hpp"

namespace jhoyt::mf::gpu
{

    class blend_state final
    {
    public:
        static blend_state basic_blend_state()
        {
            return blend_state{}
                .enable_blend(true)
                .color_blend_op(blend_op::add)
                .alpha_blend_op(blend_op::add)
                .src_color_blend_factor(blend_factor::src_alpha)
                .dst_color_blend_factor(blend_factor::one_minus_src_alpha)
                .src_alpha_blend_factor(blend_factor::src_alpha)
                .dst_alpha_blend_factor(blend_factor::one_minus_src_alpha);
        }

        auto src_color_blend_factor() const
        {
            return src_color_blend_factor_;
        }

        auto dst_color_blend_factor() const
        {
            return dst_color_blend_factor_;
        }

        auto color_blend_op() const
        {
            return color_blend_op_;
        }

        auto src_alpha_blend_factor() const
        {
            return src_alpha_blend_factor_;
        }

        auto dst_alpha_blend_factor() const
        {
            return dst_alpha_blend_factor_;
        }

        auto alpha_blend_op() const
        {
            return alpha_blend_op_;
        }

        const auto &color_write_mask() const
        {
            return color_write_mask_;
        }

        auto enable_blend() const
        {
            return enable_blend_;
        }

        auto enable_color_write_mask() const
        {
            return enable_color_write_mask_;
        }

        blend_state &src_color_blend_factor(blend_factor value)
        {
            src_color_blend_factor_ = value;
            return *this;
        }

        blend_state &dst_color_blend_factor(blend_factor value)
        {
            dst_color_blend_factor_ = value;
            return *this;
        }

        blend_state &color_blend_op(blend_op value)
        {
            color_blend_op_ = value;
            return *this;
        }

        blend_state &src_alpha_blend_factor(blend_factor value)
        {
            src_alpha_blend_factor_ = value;
            return *this;
        }

        blend_state &dst_alpha_blend_factor(blend_factor value)
        {
            dst_alpha_blend_factor_ = value;
            return *this;
        }

        blend_state &alpha_blend_op(blend_op value)
        {
            alpha_blend_op_ = value;
            return *this;
        }

        blend_state &color_write_mask(const color_component_flags value)
        {
            color_write_mask_ = value;
            return *this;
        }

        blend_state &enable_blend(bool value)
        {
            enable_blend_ = value;
            return *this;
        }

        blend_state &enable_color_write_mask(bool value)
        {
            enable_color_write_mask_ = value;
            return *this;
        }

    private:
        blend_factor src_color_blend_factor_ = blend_factor::invalid;
        blend_factor dst_color_blend_factor_ = blend_factor::invalid;
        blend_op color_blend_op_ = blend_op::invalid;
        blend_factor src_alpha_blend_factor_ = blend_factor::invalid;
        blend_factor dst_alpha_blend_factor_ = blend_factor::invalid;
        blend_op alpha_blend_op_ = blend_op::invalid;
        color_component_flags color_write_mask_;
        bool enable_blend_ = false;
        bool enable_color_write_mask_ = false;
    };

} // namespace jhoyt::mf::gpu
