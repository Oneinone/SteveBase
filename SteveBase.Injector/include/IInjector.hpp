#pragma once

#include <stdafx.hpp>
#include <Process.hpp>

namespace SteveBase::Injector {
  using namespace std;

  class IInjector {
  public:
    virtual ~IInjector() {}
    virtual DWORD GetAccessMask() = 0;
    virtual void Inject(Process process, string dllPath) = 0;
  };
}