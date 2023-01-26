#pragma once

namespace SRDT {
    class Module {
    public:
        Module() = default;
        virtual ~Module() = default;
        [[nodiscard]] virtual bool CanDraw() const;
        virtual void Draw() = 0;
    };
}
