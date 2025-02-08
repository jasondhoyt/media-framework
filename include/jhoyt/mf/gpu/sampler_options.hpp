// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

#include "compare_op.hpp"

namespace jhoyt::mf::gpu
{

    class sampler_options final
    {
    public:
        auto mip_lod_bias() const
        {
            return mip_lod_bias_;
        }

        auto max_anistropy() const
        {
            return max_anistropy_;
        }

        auto compare_op() const
        {
            return compare_op_;
        }

        auto min_lod() const
        {
            return min_lod_;
        }

        auto max_lod() const
        {
            return max_lod_;
        }

        auto enable_anistropy() const
        {
            return enable_anistropy_;
        }

        auto enable_compare() const
        {
            return enable_compare_;
        }

        sampler_options &mip_lod_bias(float value)
        {
            mip_lod_bias_ = value;
            return *this;
        }

        sampler_options &max_ansitropy(float value)
        {
            max_anistropy_ = value;
            return *this;
        }

        sampler_options &compare_op(enum compare_op value)
        {
            compare_op_ = value;
            return *this;
        }

        sampler_options &min_lod(float value)
        {
            min_lod_ = value;
            return *this;
        }

        sampler_options &max_lod(float value)
        {
            max_lod_ = value;
            return *this;
        }

        sampler_options &enable_anistropy(bool value)
        {
            enable_anistropy_ = value;
            return *this;
        }

        sampler_options &enable_compare(bool value)
        {
            enable_compare_ = value;
            return *this;
        }

    private:
        float mip_lod_bias_ = 0.0f;
        float max_anistropy_ = 0.0f;
        enum compare_op compare_op_ = compare_op::invalid;
        float min_lod_ = 0.0f;
        float max_lod_ = 0.0f;
        bool enable_anistropy_ = false;
        bool enable_compare_ = false;
    };

} // namespace jhoyt::mf::gpu
