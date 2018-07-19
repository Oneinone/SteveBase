#pragma once

#include <stdafx.hpp>

namespace SteveBase::Injector {
  using namespace std;

  class SmartHandle {
    shared_ptr<void> m_ptr;

  public:
    SmartHandle(HANDLE handle, decltype(&CloseHandle) closeFn = ::CloseHandle) : m_ptr(handle, closeFn) {
      if (!IsValidHandle()) {
        throw runtime_error{ text("Handle passed is not valid") };
      }
    }

    SmartHandle() = default;

    bool IsValidHandle() {
      return m_ptr.get() != nullptr && m_ptr.get() != INVALID_HANDLE_VALUE;
    }

    operator HANDLE() {
      return m_ptr.get();
    }
  };
}
