#pragma once

#include <string>
#include <experimental/generator>

namespace SteveBase::SourceEngine::Structure {
    using namespace std::experimental;
    struct RecvTable;

    struct ClientClass {
    private:
        int __pad0[2];
        const char *m_pNetworkName;
        RecvTable *m_pRecvTable;
        ClientClass *m_pNext;
        int m_ClassID;

    public:
        std::string GetName() const {
            return m_pNetworkName;
        }

        RecvTable *GetTable() const {
            return m_pRecvTable;
        }

        ClientClass *GetNextClass() const {
            return m_pNext;
        }

        int GetClassId() const {
            return m_ClassID;
        }

        generator<ClientClass *> TraverseList() {
            for (auto it = this; it != nullptr; it = it->GetNextClass()) {
                co_yield it;
            }
        }
    };
}