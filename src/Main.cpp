#include "Events.hpp"
#include "Hooks.hpp"
#include "Logging.hpp"
#include "Renderer.hpp"
#include "modules/GlobalVariables.hpp"
#include "modules/Logger.hpp"
#include "modules/Scripts.hpp"
#include "modules/Stats.hpp"

namespace {
    void RegisterEvents() {
        auto& eventProcessor = SRDT::Events::EventProcessor::GetSingleton();
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(&eventProcessor);
        logger::trace("Events registered.");
    }

    void RegisterModules() {
        auto& renderer = SRDT::Renderer::GetSingleton();
        renderer.RegisterModule(std::make_unique<SRDT::Modules::GlobalVariables>());
        renderer.RegisterModule(std::make_unique<SRDT::Modules::Logger>());
        renderer.RegisterModule(std::make_unique<SRDT::Modules::Scripts>());
        renderer.RegisterModule(std::make_unique<SRDT::Modules::Stats>());
        logger::trace("Render modules registered.");
    }
}

SKSEPluginLoad([[maybe_unused]] const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SRDT::Logging::Setup();
    SRDT::Hooks::Setup();
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            RegisterEvents();
            RegisterModules();
        } else if (message->type == SKSE::MessagingInterface::kPostLoadGame) {
            SRDT::Modules::GlobalVariables::UpdateData(true);
        }
    });
    return true;
}
