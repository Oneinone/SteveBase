#include <GlobalDefines.hpp>
#include <manager/StateManager.hpp>

namespace SteveBase::Manager {
    bool StateManager::m_isMenuActivated = false;

    bool StateManager::IsMenuActivated() {
        return m_isMenuActivated;
    }
}