// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <SDL3/SDL_init.h>

#include "bitflags.hpp"

namespace jhoyt::mf
{

    enum class subsystem : uint32_t
    {
        audio = SDL_INIT_AUDIO,
        video = SDL_INIT_VIDEO,
        joystick = SDL_INIT_JOYSTICK,
        haptic = SDL_INIT_HAPTIC,
        gamepad = SDL_INIT_GAMEPAD,
        events = SDL_INIT_EVENTS,
        sensor = SDL_INIT_SENSOR,
        camera = SDL_INIT_CAMERA
    };

    using subsystem_flags = bitflags<subsystem, uint32_t>;

} // namespace jhoyt::mf