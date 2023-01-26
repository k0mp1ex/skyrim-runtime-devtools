#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    class GlobalVariables : public Module {
    public:
        GlobalVariables() = default;
        ~GlobalVariables() override = default;
        void Draw() override;
    };
}
