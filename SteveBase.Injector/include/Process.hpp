#pragma once

#include <stdafx.hpp>
#include <SmartHandle.hpp>
#include <Memory.hpp>
#include <codecvt>

namespace SteveBase::Injector {
  using namespace std;
  
  class Process {
    SmartHandle m_processHandle;
  public:
    void SetHandle(SmartHandle processHandle) {
      m_processHandle = processHandle;
      if (!m_processHandle.IsValidHandle()) {
        throw runtime_error{ text("The handle supplied is not valid") };
      }
    }

    Process(SmartHandle processHandle) {
      SetHandle(processHandle);
    }

    Process(string processName, DWORD desiredAccess, bool waitForProcess = true) {
      shared_ptr<PROCESSENTRY32> pe;
      for (; (pe = GetProcessEntryByName(processName)) == nullptr; Sleep(100)) {
        if (!waitForProcess) {
          throw runtime_error{ ggformat_to_string(text(R"(Process "{0}" not found)"), processName) };
        }
      }

      SetHandle(OpenProcess(desiredAccess, false, pe->th32ProcessID));
    }

    Process(wstring processName, DWORD desiredAccess, bool waitForProcess = true) {
      shared_ptr<PROCESSENTRY32W> pe;
      for (; (pe = GetProcessEntryByName(processName)) == nullptr; Sleep(100)) {
        if (!waitForProcess) {
          throw runtime_error{ ggformat_to_string(text(R"(Process "{0}" not found)"), wstring_convert<codecvt_utf8<wchar_t>, wchar_t>{}.to_bytes(processName)) };
        }
      }

      SetHandle(OpenProcess(desiredAccess, false, pe->th32ProcessID));
    }

    SmartHandle GetProcessHandle() {
      return m_processHandle;
    }

    operator SmartHandle() {
      return GetProcessHandle();
    }

    operator HANDLE() {
      return GetProcessHandle();
    }

    void ReadMemory(uintptr_t address, uintptr_t buffer, size_t bufferSize) {
      ReadProcessMemory(m_processHandle, address, buffer, bufferSize);
    }

    template<class T>
    void ReadMemory(uintptr_t address, T *buffer) {
      try {
        ReadProcessMemory(m_processHandle, address, buffer);
      } catch (...) {
        throw;
      }
    }

    template<class T>
    T ReadMemory(uintptr_t address) {
      try {
        return ReadProcessMemory<T>(m_processHandle, address);
      } catch (...) {
        throw;
      }
    }

    void WriteMemory(uintptr_t address, uintptr_t buffer, size_t bufferSize) {
      WriteProcessMemory(m_processHandle, address, buffer, bufferSize);
    }

    template<class T>
    void WriteMemory(uintptr_t address, T *buffer) {
      try {
        WrtieProcessMemory<T>(m_processHandle, address, buffer);
      } catch (...) {
        throw;
      }
    }

    template<class T>
    void WriteMemory(uintptr_t address, T &buffer) {
      try {
        WrtieProcessMemory<T>(m_processHandle, address, &buffer);
      } catch (...) {
        throw;
      }
    }

    static shared_ptr<PROCESSENTRY32> GetProcessEntryByName(string name);
    static shared_ptr<PROCESSENTRY32W> GetProcessEntryByName(wstring name);
  };
}
