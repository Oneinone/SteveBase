#pragma once

#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct RecvTable;
    struct RecvProp;
    struct CRecvProxyData;

    using RecvVarProxyFn = void(*)(const CRecvProxyData *pData, void *pStruct, void *pOut);
    using DataTableRecvVarProxyFn = void(*)(const RecvProp *pProp, void **pOut, void *pData, int objectID);

    struct RecvProp {
    private:
        const char *m_pVarName;
        Pad(sizeof(int32_t) * 3);
        Pad(sizeof(bool));
        Pad(sizeof(int32_t) * 3);
        RecvVarProxyFn			m_ProxyFn;
        DataTableRecvVarProxyFn	m_DataTableProxyFn;	// For RDT_DataTable.

        RecvTable *m_pDataTable;
        int m_iOffset;
        Pad(sizeof(int32_t) * 3);

    public:
        const char * GetName() const { return m_pVarName; }
        int GetOffset() const { return m_iOffset; }
        RecvTable *GetDataTable() const { return m_pDataTable; }
    };
}