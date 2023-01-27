#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    class Stats : public Module {
    public:
        Stats() = default;
        ~Stats() override = default;
        void Draw() override;
    };
}
