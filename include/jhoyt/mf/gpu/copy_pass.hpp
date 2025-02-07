// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_gpu.h>

namespace jhoyt::mf::gpu
{

    class copy_pass final
    {
    public:
        ~copy_pass();

        copy_pass(const copy_pass &) = delete;
        copy_pass &operator=(const copy_pass &) = delete;

        copy_pass(copy_pass &&) = delete;
        copy_pass &operator=(copy_pass &&) = delete;

        auto ptr() const
        {
            return ptr_;
        }

        friend class command_buffer;

    private:
        SDL_GPUCopyPass *ptr_;

        copy_pass(SDL_GPUCommandBuffer *cmd_buf);
        void end();
    };

} // namespace jhoyt::mf::gpu
