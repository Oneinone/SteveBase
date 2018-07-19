#pragma once

#include <experimental/generator>

namespace SteveBase::SourceEngine::Structure {
    using namespace std::experimental;

    // Used internally to register classes.
    struct InterfaceReg {
        using InstantiateInterfaceFn = void*(*)();

        InstantiateInterfaceFn	m_CreateFn; // returns a global pointer to the implmented class
        const char				*m_pName; // Registry name
        InterfaceReg			*m_pNext; // Next registry entry, nullptr if last entry

    public:
        auto &GetFunctionFactory() {
            return m_CreateFn;
        }
        void *GetPointer() {
            return m_CreateFn();
        }
        const char *GetName() {
            return m_pName;
        }
        InterfaceReg *GetNext() {
            return m_pNext;
        }

        // some nextgen cutting edge shit
        // use it in the first entry of the registry please
        generator<InterfaceReg *> Traverse() {
            for (auto ptr = this; ptr != nullptr; ptr = ptr->GetNext()) {
                co_yield ptr;
            }
        }
    };
}