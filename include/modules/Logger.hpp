#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    class Logger : public Module {
    public:
        Logger() = default;
        ~Logger() override = default;
        void Draw() override;
    };
}
