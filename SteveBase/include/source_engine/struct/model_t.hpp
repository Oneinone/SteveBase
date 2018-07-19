#pragma once

#include <string>

namespace SteveBase::SourceEngine::Structure {
    struct model_t {
    private:
        void *m_unkHandle;
        char m_name[255];

    public:
        std::string GetName() const { return std::string(m_name, 255); }
    };
}