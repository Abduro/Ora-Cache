#ifndef _VIRT_CAMERA_H_INCLUDED
#define _VIRT_CAMERA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 09:57:34.050, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera interface declaration file;
*/
#include "math.defs.h"
#include "math.matrix.h"
#include "math.quat.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl { using namespace shared::defs; using namespace ex_ui::draw::open_gl::math;
namespace camera { namespace opers {

	class CForward {
	public:
		CForward (void); CForward (const CForward&) = delete; CForward (CForward&&) = delete; ~CForward (void) = default;
	private:
		CForward& operator = (const CForward&) = delete;  CForward& operator = (CForward&&) = delete;
	};

	class CPosition { // position class for camera movement;
	public:
		CPosition (void); CPosition (const CPosition&) = delete; CPosition (CPosition&&) = delete; ~CPosition (void) = default;
	private:
		CPosition& operator = (const CPosition&) = delete;  CPosition& operator = (CPosition&&) = delete;
	};

	class CRotation {
	public:
		CRotation (void); CRotation (const CRotation&) = delete; CRotation (CRotation&&) = delete; ~CRotation (void) = default;
	private:
		CRotation& operator = (const CRotation&) = delete;  CRotation& operator = (CRotation&&) = delete;
		c_mat4x4 m_rotate; // 4x4 matrix for rotation only;
		s_quat   m_quat ;  // quaternion for rotations;
		c_mat4x4 m_trans;  // 4x4 matrix combined rotation and translation;
	};

	class CTarget {
	public:
		CTarget (void); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete; ~CTarget (void) = default;
	private:
		CTarget& operator = (const CTarget&) = delete;  CTarget& operator = (CTarget&&) = delete;
	};
}}

	class CVirtCamera {
	public:
		CVirtCamera (void); CVirtCamera (const CVirtCamera&) = delete; CVirtCamera (CVirtCamera&&) = delete; ~CVirtCamera (void) = default;
		TError& Error (void) const;
	protected:
		CVirtCamera& operator = (const CVirtCamera&) = delete; CVirtCamera& operator = (CVirtCamera&&) = delete;
		CError m_error;
		float  m_dist;   // distance between position and target;
		vec_3  m_pos ;   // camera position at world space;
		vec_3  m_target; // camera focal(lookat) position at world space;
	};

}}}

#endif/*_VIRT_CAMERA_H_INCLUDED*/