#pragma once

#include <experimental/generator>
#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace std::experimental;
    struct RecvProp;

    struct RecvTable {
    private:
        RecvProp *m_pProps;
        int m_nProps;
        Pad(0x4);
        const char *m_pNetTableName;
        Pad(0x2);

    public:
        RecvProp *GetProperties() const { return m_pProps; }
        int GetPropertiesCount() const { return m_nProps; }
        const char *GetName() const { return m_pNetTableName; }

        generator<RecvProp *> TraversePropsList() {
            if (GetProperties() != nullptr && GetPropertiesCount() > 0) {
                for (auto i = 0; i < GetPropertiesCount(); i++) {
                    co_yield &GetProperties()[i];
                }
            }
        }
    };
}