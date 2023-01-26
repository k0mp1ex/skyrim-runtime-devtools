#include "Events.hpp"
#include "Hooks.hpp"
#include "Logging.hpp"
#include "Renderer.hpp"

SKSEPluginLoad([[maybe_unused]] const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SRDT::Logging::Setup();
    SRDT::Hooks::Setup();
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            SRDT::Events::Setup();
            SRDT::D3D::Setup();
        }
    });
    return true;
}
