#pragma once

namespace SRDT::Events {
    class EventProcessor : public RE::BSTEventSink<RE::InputEvent*> {
    private:
        EventProcessor() = default;
        ~EventProcessor() override = default;
    public:
        EventProcessor(const EventProcessor&) = delete;
        EventProcessor(EventProcessor&&) = delete;
        EventProcessor& operator=(const EventProcessor&) = delete;
        EventProcessor& operator=(EventProcessor&&) = delete;
        RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>* a_eventSource) override;

        static EventProcessor& GetSingleton() {
            static EventProcessor singleton;
            return singleton;
        }
    };
}
