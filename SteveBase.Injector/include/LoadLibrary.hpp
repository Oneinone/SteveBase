#pragma once

#include <IInjector.hpp>

#undef LoadLibrary // fuck you ms

namespace SteveBase::Injector {
  class LoadLibrary : public IInjector {
    DWORD GetAccessMask() override final {
      return PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
    }
    void Inject(Process process, string dllPath) override final;
  };
}