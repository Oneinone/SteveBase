#include <GlobalDefines.hpp>
#include <source_engine\struct\KeyValues.hpp>

#include <Interface.hpp>
#include <source_engine\index.hpp>

#include <cstring>

// handle to a KeyValues key name symbol
typedef int HKeySymbol;
#define INVALID_KEY_SYMBOL (-1)

namespace SteveBase::SourceEngine::Structure {
    using namespace Virtual;

    KeyValues::KeyValues() {
        Init();
    }

    KeyValues::~KeyValues() {
        KeyValues *dat;
        KeyValues *datNext = nullptr;
        for (dat = m_pSub; dat != nullptr; dat = datNext) {
            datNext = dat->m_pPeer;
            dat->m_pPeer = nullptr;
            delete dat;
        }

        for (dat = m_pPeer; dat && dat != this; dat = datNext) {
            datNext = dat->m_pPeer;
            dat->m_pPeer = nullptr;
            delete dat;
        }

        delete[] m_sValue;
        m_sValue = nullptr;
        delete[] m_wsValue;
        m_wsValue = nullptr;
    }

    void KeyValues::Init() {
        m_iKeyName = INVALID_KEY_SYMBOL;
        m_iDataType = (char) types_t::None;

        m_pSub = nullptr;
        m_pPeer = nullptr;
        m_pChain = nullptr;

        m_sValue = nullptr;
        m_wsValue = nullptr;
        m_pValue = nullptr;

        m_bHasEscapeSequences = false;
        m_bEvaluateConditionals = true;

        memset(unused, 0, sizeof(unused));
    }

    // credits: https://www.unknowncheats.me/forum/counterstrike-global-offensive/242726-fix-tier0-dll-exception-closing-game-chams-related.html
    void *KeyValues::operator new(size_t allocSize) {
        return allocSize > 0 ? Get<IKeyValuesSystem>()->AllocKeyValuesMemory(allocSize) : nullptr;
    }
    void KeyValues::operator delete(void *mem) {
        if (mem != nullptr) {
            Get<IKeyValuesSystem>()->FreeKeyValuesMemory(mem);
        }
    }
}