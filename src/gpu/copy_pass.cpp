// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <cassert>
#include <stdexcept>

#include "jhoyt/mf/gpu/copy_pass.hpp"

#include "jhoyt/mf/gpu/command_buffer.hpp"

namespace jhoyt::mf::gpu
{

    copy_pass::copy_pass(SDL_GPUCommandBuffer *cmd_buf) : ptr_(SDL_BeginGPUCopyPass(cmd_buf))
    {
        if (!ptr_)
        {
            throw std::runtime_error{SDL_GetError()};
        }
    }

    copy_pass::~copy_pass()
    {
        if (ptr_)
        {
            SDL_EndGPUCopyPass(ptr_);
        }
    }

    void copy_pass::end()
    {
        if (ptr_)
        {
            SDL_EndGPUCopyPass(ptr_);
            ptr_ = nullptr;
        }
    }

} // namespace jhoyt::mf::gpu
