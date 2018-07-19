#include <stdafx.hpp>

#include <Process.hpp>

namespace SteveBase::Injector {
  shared_ptr<PROCESSENTRY32> Process::GetProcessEntryByName(string name) {
    auto pe = make_shared<PROCESSENTRY32>();
    pe->dwSize = sizeof(PROCESSENTRY32);

    SmartHandle snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (!snapshot.IsValidHandle()) {
      throw runtime_error { text("Tool helper cannot be created") };
    }

    if (!Process32First(snapshot, pe.get())) {
      throw runtime_error { text("Tool helper cannot retrieve the first entry of process list") };
    }

    do { // dont miss the first entry
      if (string(pe->szExeFile).find(name.c_str(), 0, name.length()) != string::npos) {
        return pe;
      }
    } while (Process32Next(snapshot, pe.get()));

    return nullptr;
  }

  shared_ptr<PROCESSENTRY32W> Process::GetProcessEntryByName(wstring name) {
    auto pe = make_shared<PROCESSENTRY32W>();
    pe->dwSize = sizeof(PROCESSENTRY32W);

    SmartHandle snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (!snapshot.IsValidHandle()) {
      throw runtime_error { text("Tool helper cannot be created") };
    }

    if (!Process32FirstW(snapshot, pe.get())) {
      throw runtime_error{ text("Tool helper cannot retrieve the first entry of process list") };
    }

    do { // dont miss the first entry
      if (wstring(pe->szExeFile).find(name.c_str(), 0, name.length()) != string::npos) {
        return pe;
      }
    } while (Process32NextW(snapshot, pe.get()));

    return nullptr;
  }
}
