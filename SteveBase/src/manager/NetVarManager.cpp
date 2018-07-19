#include <GlobalDefines.hpp>
#include <manager/NetVarManager.hpp>

#define DumpNetvar false

#define ShouldDumpNetvarAtRunTime !RELEASE && DumpNetvar

#include <Interface.hpp>
#include <source_engine/index.hpp>
#include <vendor/hash/hash.h>

#if ShouldDumpNetvarAtRunTime
#include <utility/GameUtility.hpp>
#include <vendor/nlohmann/json.hpp>
#endif

#if DEBUG
#include <utility/Logger.hpp>
#endif

namespace SteveBase::Manager {
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;
#if ShouldDumpNetvarAtRunTime
    using namespace Utility;
#endif

    JudyHashArray<int> netvar;
    // array<int, 65535> netvar;

    static void dumpTable(RecvTable *table) {
        // get the hash of the table name
        const auto tableHash = run_time_hash(table->GetName());

        // table is invalid
        if (table == nullptr) return;

        for (auto prop : table->TraversePropsList()) {
            // calculate the combine hash
            const auto hash = tableHash * run_time_hash(prop->GetName());

            // if the hash wasn't found, set it
            if (netvar.find(hash) == netvar.end()) netvar[hash] = prop->GetOffset();

            // recursive scan to the children table
            if (prop->GetDataTable() != nullptr) dumpTable(prop->GetDataTable());
        }

    };

    void NetVarManager::Init() {
        // netvar.fill(-1);


        // start the actual iteration
        for (auto klass : Get<IBaseClientDLL>()->GetAllClasses()->TraverseList()) {
            dumpTable(klass->GetTable());
        }


#if ShouldDumpNetvarAtRunTime
        SaveNetVarJsonToDisk();
        LoggerNotice(ggformat_to_string("Netvar saved to {0}", GameUtility::GetHackDirectory() + "netvars.json"));
#endif
    }

    int NetVarManager::GetNetVar(const netvar_hash_t hash) {
        return netvar[hash];
        // return netvar[hash % netvar.size()];
    }

#if ShouldDumpNetvarAtRunTime
    // ghetto dumepr
    string NetVarManager::DumpAsJson() {
        nlohmann::json j;

        function<void(RecvTable *)> dumpTable = [&](RecvTable *table) {
            // table is invalid
            if (table == nullptr) return;

            // property is invalid OR there is no property
            if (table->GetProperties() == nullptr || table->GetPropertiesCount() < 1) return;

            // iterate thtough the table
            for (int i = 0; i < table->GetPropertiesCount(); i++) {
                auto prop = table->GetProperties()[i]; // reference to the property

                j[table->GetName()][prop.GetName()] = ggformat_to_string("0x{0:X}", prop.GetOffset());

                // recursive scan to the children table
                if (prop.GetDataTable() != nullptr) dumpTable(prop.GetDataTable());
            }
        };

        // start the actual iteration
        for (auto cur = Get<IBaseClientDLL>()->GetAllClasses(); cur; cur = cur->GetNextClass()) {
            dumpTable(cur->GetTable());
        }

        /*
        // the part it gets ghetto
        map<string, map<string, int>> ordered;

        for (auto it1 : m_netvar) {
          auto dataTableName = it1.first;
          for (auto it2 : it1.second) {
            auto varName = it2.first;
            auto offset = it2.second;
            ordered[dataTableName][varName] = offset;
          }
        }

        for (auto it1 : ordered) {
          auto dataTableName = it1.first;
          for (auto it2 : it1.second) {
            auto varName = it2.first;
            auto offset = it2.second;
            j[dataTableName][varName] = ggformat_to_string("0x{0:X}", offset); // another ghetto
          }
        }
        */

        return j.dump(2);
    }
    void NetVarManager::SaveNetVarJsonToDisk() {
        ofstream file(GameUtility::GetHackDirectory() + text("netvars.json"));
        if (file.is_open()) {
            file << DumpAsJson();
        }
        file.close();
        LoggerNotice("NetVar Dumped.");
    }
#endif
}