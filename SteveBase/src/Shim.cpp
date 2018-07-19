namespace std {
    const char *__cdecl _Syserror_map(int _Errcode) {
        return nullptr;
    }

    int __cdecl _Winerror_map(int _Errcode) {
        return 0;
    }
    
    unsigned long __cdecl _Winerror_message(unsigned long _Message_id, char *_Narrow, unsigned long _Size) {
        return 0;
    }
}