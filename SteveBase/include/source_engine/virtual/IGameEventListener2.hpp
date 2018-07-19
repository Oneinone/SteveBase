#pragma once

#include <functional>

namespace SteveBase::SourceEngine::Virtual {
    interface IGameEvent;

    interface IGameEventListener2 {
        virtual	~IGameEventListener2() {}
        // FireEvent is called by EventManager if event just occured
        // KeyValue memory will be freed by manager if not needed anymore
        virtual void FireGameEvent(IGameEvent *event) = 0;
    };

    class LambdaGameEventListener implements IGameEventListener2 {
    public:
        LambdaGameEventListener(std::function<void(IGameEvent *)> fn) {
            m_fn = fn;
        }

        void FireGameEvent(IGameEvent *event) final {
            m_fn(event);
        }

    private:
        std::function<void(IGameEvent *)> m_fn;
    };
}