#pragma once

#include <misc/Macro.hpp>
#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    // TODO
    interface IConVar extends Misc::ProxiedClass {
        DefineVFunc(GetName, () -> const char *)(8)();
        DefineVFunc(SetValue, (const char *value) -> void)(14)(value);

    private:
        Pad(0x4); //0x0000
    public:
        IConVar* m_pNext; //0x0004 
        __int32 m_bRegistered; //0x0008 
        char* m_pszName; //0x000C 
        char* m_pszHelpString; //0x0010 
        __int32 m_nFlags; //0x0014 
    private:
        Pad(0x4); //0x0018
    public:
        IConVar* m_pParent; //0x001C 
        char* m_pszDefaultValue; //0x0020 
        char* m_strString; //0x0024 
        __int32 m_StringLength; //0x0028 
        float m_fValue; //0x002C 
        __int32 m_nValue; //0x0030 
        __int32 m_bHasMin; //0x0034 
        float m_fMinVal; //0x0038 
        __int32 m_bHasMax; //0x003C 
        float m_fMaxVal; //0x0040 
        void* m_fnChangeCallback; //0x0044 
    };
}
