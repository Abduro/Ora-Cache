#ifndef _CAMERA_BASE_H_INCLUDED
#define _CAMERA_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-May-2026 at 01:26:29.672, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' virtual camera base interface declaration file;
*/
#include "drawable.defs.h"
#include "camera.frustum.h"

namespace open_gl { using namespace shared::defs;
namespace camera {}

	using CFrustum = ::open_gl::camera::CFrustum;
	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;

	class CCamera {
	public:
		using s_angles = ::open_gl::views::s_angles;
		using s_pos = ::open_gl::views::s_pos;
		CCamera (void); CCamera (const CCamera&) = delete; CCamera (CCamera&&) = delete; ~CCamera (void) = default;
		const
		s_angles& Angles (void) const;
		s_angles& Angles (void) ;

		err_code  Create  (void);
		err_code  Destroy (void);

		float     Dist (void) const;  // gets the distance from x-y-pane to the camera;
		float&    Dist (void) ;       // gets the reference to distance attribute of this class for making possible direct assigning the value;

		TError&   Error (void) const;
		const
		CFrustum& Frustum (void) const;
		CFrustum& Frustum (void);
		const
		s_pos&    Pos (void) const;
		s_pos&    Pos (void);
		const
		c_mat4x4& View (void) const;
		c_mat4x4& View (void);

	private:
		CCamera& operator = (const CCamera&) = delete; CCamera& operator = (CCamera&&) = delete;
		mutable
		CError   m_error;
		s_pos    m_pos;
		s_angles m_angles;
		c_mat4x4 m_view;
		float    m_dist;    // https://www.allacronyms.com/distance/abbreviated ;
		CFrustum m_frustum;
	};
}

#endif/*_CAMERA_BASE_H_INCLUDED*/