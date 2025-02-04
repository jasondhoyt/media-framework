// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL3/SDL_gpu.h>

#include "shader_format.hpp"

namespace jhoyt::mf
{

    class context;
    class window;

    namespace gpu
    {

        class device final
        {
        public:
            static std::shared_ptr<device> create(std::shared_ptr<context> ctx,
                                                  shader_format_flags format_flags,
                                                  bool debug_mode = false,
                                                  const std::string &name = {});

            ~device();

            device(const device &) = delete;
            device &operator=(const device &) = delete;

            device(device &&) = delete;
            device &operator=(device &&) = delete;

            void claim_window(std::shared_ptr<window> window);
            void release_window(const std::shared_ptr<window> &window);

            auto ptr() const
            {
                return ptr_;
            }

        private:
            std::shared_ptr<context> ctx_;
            SDL_GPUDevice *ptr_;
            std::vector<std::shared_ptr<window>> windows_;

            device(std::shared_ptr<context> ctx, SDL_GPUDevice *ptr);
        };

    } // namespace gpu

} // namespace jhoyt::mf
