#pragma once

#include <windows.h>

#include <memory>

namespace SteveBase::Utility {

    class SmartHandle : public std::shared_ptr<void> {
    public:
        SmartHandle(HANDLE handle) {
            std::shared_ptr<void>(handle, CloseHandle);
        }
    };
}
