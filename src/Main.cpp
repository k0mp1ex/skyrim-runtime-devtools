#include "Events.hpp"
#include "Hooks.hpp"
#include "Logging.hpp"

SKSEPluginLoad([[maybe_unused]] const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SRDT::Logging::Setup();
    SRDT::Hooks::Setup();
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            SRDT::Events::Setup();
            RE::ConsoleLog::GetSingleton()->Print("Hello, SRDT!");
            logger::trace("Hello, SRDT!");
        }
    });
    return true;
}
