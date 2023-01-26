#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    class HelloWorld : public Module {
    public:
        HelloWorld() = default;
        ~HelloWorld() override = default;
        void Draw() override;
    };
}
