#pragma once

#include <windows.h>

#include <memory>

namespace SteveBase::Utility {

    class SmartVirtualMemory {
        struct SmartVirtualMemoryInfo {
            HANDLE m_handle;
            DWORD m_size;
            LPVOID m_mem;
            DWORD m_freeType;
        };
        std::shared_ptr<SmartVirtualMemoryInfo> shared;

    public:
        SmartVirtualMemory(HANDLE handle, LPVOID mem, DWORD size, DWORD freeType) {
            shared = std::shared_ptr<SmartVirtualMemoryInfo>(new SmartVirtualMemoryInfo, [=](SmartVirtualMemoryInfo *info) {
                info->m_handle
                    ? VirtualFreeEx(info->m_handle, info->m_mem, info->m_size, info->m_freeType)
                    : VirtualFree(info->m_mem, info->m_size, info->m_freeType);
            });

            shared->m_handle = handle;
            shared->m_size = size;
            shared->m_mem = mem;
            shared->m_freeType = freeType;
        }

        SmartVirtualMemory(LPVOID mem, DWORD size, DWORD freeType) {
            SmartVirtualMemory(nullptr, mem, size, freeType);
        }

        SmartVirtualMemory(HANDLE handle, LPVOID address, DWORD size, DWORD allocationType, DWORD protect, DWORD freeType) {
            SmartVirtualMemory(handle, VirtualAlloc(address, size, allocationType, protect), size, freeType);
        }

        SmartVirtualMemory(LPVOID address, DWORD size, DWORD allocationType, DWORD protect, DWORD freeType) {
            SmartVirtualMemory(nullptr, address, size, allocationType, protect, freeType);
        }

        HANDLE getHandle() {
            return shared->m_handle;
        }
        LPVOID getMemory() {
            return shared->m_mem;
        }
        DWORD getSize() {
            return shared->m_size;
        }

    };
}