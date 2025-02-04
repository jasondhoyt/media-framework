// Copyright (c) 2025-present, Jason Hoyt
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <memory>

namespace jhoyt::mf
{

    class context final
    {
    public:
        static std::shared_ptr<context> create();

        ~context();

        context(const context &) = delete;
        context &operator=(const context &) = delete;

        context(context &&) = delete;
        context &operator=(context &&) = delete;

    private:
        context();
    };

} // namespace jhoyt::mf
