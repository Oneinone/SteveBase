#include <stdafx.hpp>

#include <LoadLibrary.hpp>

#include <Process.hpp>

using namespace std;
using namespace SteveBase::Injector;

string GetFullPathForFile(string str) {
    char buf[MAX_PATH] = { 0 };
    const auto len = GetFullPathName(str.c_str(), MAX_PATH, buf, nullptr);
    return string(buf, len);
}

unordered_map<std::string, IInjector *> injectors {
    { text("LoadLibrary"), new LoadLibrary }
};

int main(int argc, const char *argv[]) {
    argc--;

    try {
        if (argc < 2) { // textapp for env and two for process name and dll path
            throw runtime_error{ text("Usage: inject.exe <process name> <dll path> <optional: delay> <optional: injection method>") };
        }

        const string processName = string(argv[0 + 1]);
        const string dllPath = GetFullPathForFile(argv[1 + 1]);
        const int delay = argc >= 3 ? stoi(argv[2 + 1]) : 0;
        const string method = argc >= 4 ? string(argv[3 + 1]) : text("LoadLibrary");

        if (injectors.find(method) == injectors.end()) {
            throw_with_nested(runtime_error(ggformat_to_string(text("No such injection method: {0}"), method)));
        }

        shared_ptr<IInjector> inject(injectors[method]);

        if (!ifstream(dllPath).good()) {
            throw_with_nested(runtime_error(text("DLL File Specified Is Invalid, Lost or Not Found")));
        }

        ggprint(text("[=] Process name: {0}...\n"), argv[1]);
        ggprint(text("[=] DLL Path: {0}...\n"), dllPath);
        delay > 0 ? ggprint(text("[=] Delay: {0} miliseconds...\n\n"), delay) : 0;
        ggprint(text("[=] Using injection method: {0}...\n"), dllPath);

        cout << rang::fgB::yellow;
        ggprint(text("[=] Waiting for {0}...\n"), argv[1]);

        const Process process(string(argv[1]), inject->GetAccessMask());
        cout << rang::fgB::green;
        ggprint(text("[=] {0} found...\n"), argv[1]);
        ggprint(text("[=] Injecting...\n"));

        inject->Inject(process, dllPath);
        Sleep(3000);

        return 1;
    } catch (runtime_error &ex) {
        cerr << rang::fgB::red;
        ggprint_to_file(stderr, text("[!] Error catched:\n"));
        ggprint_to_file(stderr, text("  [!] {0}\n"), ex.what());
        cerr << rang::style::reset;
        system(text("PAUSE"));
    }

    return 0;
}