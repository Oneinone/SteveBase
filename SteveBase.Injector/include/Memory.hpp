#pragma once

#include <stdafx.hpp>
#include <SmartHandle.hpp>

namespace SteveBase::Injector {
  inline void ReadProcessMemory(SmartHandle handle, uintptr_t address, uintptr_t buffer, size_t bufferSize) {
    SIZE_T size;
    const BOOL ret = ::ReadProcessMemory(handle, (LPCVOID)address, (LPVOID)buffer, bufferSize, &size);
    if (ret == FALSE) {
      throw runtime_error{ ggformat_to_string(text("Cannot read the memory at the specified address 0x{0:X}!"), address) };
    }
    if (size != bufferSize) {
      throw runtime_error{ text("Memory read unmatches the explicit structure size!") };
    }
  }

  inline void WriteProcessMemory(SmartHandle handle, uintptr_t address, uintptr_t buffer, size_t bufferSize) {
    SIZE_T size;
    const BOOL ret = ::WriteProcessMemory(handle, (LPVOID)address, (LPVOID)buffer, bufferSize, &size);
    if (ret == FALSE) {
      throw runtime_error{ ggformat_to_string(text("Cannot write the memory at the specified address 0x{0:X}!"), address) };
    }
    if (size != bufferSize) {
      throw runtime_error{ text("Memory written unmatches the explicit structure size!") };
    }
  }

  template<class T>
  void ReadProcessMemory(SmartHandle handle, uintptr_t address, T *buffer) {
    ReadProcessMemory(handle, address, buffer, sizeof T);
  }

  template<class T>
  T ReadProcessMemory(SmartHandle handle, uintptr_t address) {
    T buffer;
    ReadProcessMemory<T>(handle, address, &buffer);
    return buffer;
  }

  template<class T>
  void WrtieProcessMemory(SmartHandle handle, uintptr_t address, T *buffer) {
    WrtieProcessMemory<T>(handle, address, buffer, sizeof T);
  }

  template<class T>
  void WrtieProcessMemory(SmartHandle handle, uintptr_t address, T &buffer) {
    WrtieProcessMemory<T>(handle, address, &buffer);
  }
}
