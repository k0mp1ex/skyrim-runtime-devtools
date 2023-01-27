#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    struct LogData {
        std::string fileName;
    };

    class Logger : public Module {
    private:
        inline static std::vector<LogData> logs;
    public:
        Logger() = default;
        ~Logger() override = default;
        void Draw() override;

        static void UpdateData(bool forceUpdate = false) {
            //TODO: Check when the data can be updated and add update intervals
            if (!logs.empty()) {
                if (!forceUpdate) return;
                logs.clear();
            }

            if (auto scriptsFolder = logger::log_directory()) {
                for (auto& entry : std::filesystem::directory_iterator(scriptsFolder.value())) {
                    if (!entry.is_regular_file()) continue;
                    auto logFile = entry.path().filename().replace_extension().string();
                    logs.emplace_back(LogData{logFile});
                }
            }
        }
    };
}
