#ifndef _VIRT_CAMERA_H_INCLUDED
#define _VIRT_CAMERA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 09:57:34.050, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera interface declaration file;
*/
#include "math.defs.h"
#include "math.lerp.h"
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

		void Set  (const float _x_angle, const float _y_angle, const float _z_angle);
		void Set  (const s_vec_3 _angles);    // all angles are set in degrees;
		void Turn (const float _time_frame);

		const c_mat4x4&  To_matrix (void);
		const c_mat4x4&  To_matrix (const s_vec_3& _angle);

	private:
		CRotation& operator = (const CRotation&) = delete;  CRotation& operator = (CRotation&&) = delete;
#pragma region cPos::attrs
		bool     m_b_oper; // for indicating start/stop rotate operation;
		bool     m_b_quat; // for indicating to use quaternions;
		float    m_f_dura; // duration of the rotation; (secs)
		float    m_f_time; // time of starting rotation;

		s_vec_3  m_angle_from;
		s_vec_3  m_angle_to;
		s_quat   m_quat_from;
		s_quat   m_quat_to;

		c_mat4x4 m_rotate; // 4x4 matrix for rotation only;
		s_quat   m_quat ;  // quaternion for rotations;
		c_mat4x4 m_trans;  // 4x4 matrix combined rotation and translation;

		c_interp::e_mode m_mode;
#pragma endregion
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
		camera::opers::CRotation m_rotate;
	};

}}}

#endif/*_VIRT_CAMERA_H_INCLUDED*/