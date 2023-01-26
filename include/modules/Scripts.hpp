#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    class Scripts : public Module {
    public:
        Scripts() = default;
        ~Scripts() override = default;
        void Draw() override;
    };
}
