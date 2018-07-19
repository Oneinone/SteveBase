#pragma once

#include <string_view>

#include <maths/Vector2.hpp>
#include <maths/Vector3.hpp>

#include <source_engine/def/SendPropType.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Define;
    using namespace Maths;

    struct DVariant {
    private:
        union {
            float	m_Float;
            int		m_Int;
            const char	*m_pString;
            void	*m_pData;	// For DataTables.
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
            float	m_Vector[4];
#else
            float	m_Vector[3];
#endif

#ifdef SUPPORTS_INT64
            int64	m_Int64;
#endif
        };

        SendPropType	m_Type;
    public:
        float GetFloat() {
            return m_Float;
        }
        int GetInt() {
            return m_Int;
        }
        std::string_view GetString() {
            return m_pString;
        }
        void *GetUserData() {
            return m_pData;
        }
        Vector3 GetVector3() {
            return Vector3(m_Vector[0], m_Vector[1], m_Vector[2]);
        }

        Vector2 GetVector2() {
            return Vector2(m_Vector[0], m_Vector[1]);
        }

        SendPropType GetType() {
            return m_Type;
        }
    };

}
