#pragma once

#include <maths/EulerAngle.hpp>
#include <maths/Vector3.hpp>
#include <maths/ViewMatrix.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Maths;

    struct CViewSetup {
        int			x, x_old;
        int			y, y_old;
        int			width, width_old;
        int			height, height_old;
        bool		m_bOrtho;
        float		m_OrthoLeft;
        float		m_OrthoTop;
        float		m_OrthoRight;
        float		m_OrthoBottom;
        bool		m_bCustomViewMatrix;
        ViewMatrix	m_matCustomViewMatrix;
        char		pad_0x68[0x48];
        float		fov;
        float		fovViewmodel;
        Vector3		origin;
        EulerAngle	angles;
        float		zNear;
        float		zFar;
        float		zNearViewmodel;
        float		zFarViewmodel;
        float		m_flAspectRatio;
        float		m_flNearBlurDepth;
        float		m_flNearFocusDepth;
        float		m_flFarFocusDepth;
        float		m_flFarBlurDepth;
        float		m_flNearBlurRadius;
        float		m_flFarBlurRadius;
        int			m_nDoFQuality;
        int			m_nMotionBlurMode;
        float		m_flShutterTime;
        Vector3		m_vShutterOpenPosition;
        EulerAngle	m_shutterOpenAngles;
        Vector3		m_vShutterClosePosition;
        EulerAngle	m_shutterCloseAngles;
        float		m_flOffCenterTop;
        float		m_flOffCenterBottom;
        float		m_flOffCenterLeft;
        float		m_flOffCenterRight;
        int			m_EdgeBlur;
    };
}