#pragma once

#include <windows.h>

namespace SteveBase::Utility {
    class VirtualRAIIProtect {
        LPVOID m_address;
        size_t m_size;
        DWORD m_newProtect;
        DWORD m_oldProtect;

    public:
        VirtualRAIIProtect(LPVOID address, size_t size, DWORD newProtect) {
            // dont tell me why not use initialization list instead, because i dont fucking like it
            m_address = address;
            m_size = size;
            m_newProtect = newProtect;

            VirtualProtect(m_address, m_size, m_newProtect, &m_oldProtect);
        }

        ~VirtualRAIIProtect() {
            VirtualProtect(m_address, m_size, m_oldProtect, nullptr);
        }
        LPVOID GetProtectedAddress() {
            return m_address;
        }
        size_t GetProtectedSize() {
            return m_size;
        }
        DWORD GetNewProtect() {
            return m_newProtect;
        }
        DWORD GetOldProtect() {
            return m_oldProtect;
        }
    };
}