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
namespace camera {
namespace opers {
	/* 'Upfront' refers to something done in advance or at the beginning of a process (e.g., upfront costs);
	   'Forward' implies moving in a direction toward the front or future;
	*/
	class CForward {
	public:
		CForward (void); CForward (const CForward&) = delete; CForward (CForward&&) = delete; ~CForward (void) = default;
	private:
		CForward& operator = (const CForward&) = delete;  CForward& operator = (CForward&&) = delete;
	};

	class CPosition { // position class for camera movement;
	public:
		CPosition (void); CPosition (const CPosition&) = delete; CPosition (CPosition&&) = delete; ~CPosition (void) = default;
		const
		vec_3& Get (void) const; // gets the reference to the camera position coordinates; (ro)
		vec_3& Get (void);       // gets the reference to the camera position coordinates; (rw)
		void Reset (void);

	private:
		CPosition& operator = (const CPosition&) = delete;  CPosition& operator = (CPosition&&) = delete;
		vec_3  m_coords;
	};

	class CRotation {
	public:
		CRotation (void); CRotation (const CRotation&) = delete; CRotation (CRotation&&) = delete; ~CRotation (void) = default;

		const
		c_mat4x4& Get (void) const;
		c_mat4x4& Get (void);
		const
		s_quat&   Quat (void) const;
		s_quat&   Quat (void);

		void Reset(void);   // resets the camera rotation state to default: the angle of the rotation is set to 0;

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

	class CTarget { // this is a class of an object the camera 'looks' at;
	public: // https://en.wikipedia.org/wiki/List_of_glossing_abbreviations :: 'default' >> 'dflt';
		static inline const float f_dflt_dist = 10.0f; // error C2864: a static data member with an in-class initializer must have non-volatile const integral type or be specified as 'inline';
		CTarget (void); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete; ~CTarget (void) = default;

		const
		vec_3&  Angle (void) const;
		vec_3&  Angle (void);
		
		const
		float& Distance (void) const; // returns the reference to the current distance between the camera position and target; (ro)
		float& Distance (void);       // returns the reference to the current distance between the camera position and target; (rw)

		const
		vec_3&  Get (void) const;
		vec_3&  Get (void);

		void  Reset (void);

		CTarget& operator <<(const float _f_dist); // assigns the distance to given value;

	private:
		CTarget& operator = (const CTarget&) = delete;  CTarget& operator = (CTarget&&) = delete;
		vec_3  m_angle; // angle in degree around the target; x:pitch;y:yaw;z:roll;
		vec_3  m_coords;
		float  m_dist;  // https://www.abbreviations.com/abbreviation/distance ;
	};
}}

	class CVirtCamera {
	public:
		using CPosition = camera::opers::CPosition;
		using CRotation = camera::opers::CRotation;
		using CTarget   = camera::opers::CTarget  ;
	public:
		CVirtCamera (void); CVirtCamera (const CVirtCamera&) = delete; CVirtCamera (CVirtCamera&&) = delete; ~CVirtCamera (void) = default;
		TError& Error (void) const;

		err_code Look_at (void);
		err_code Look_at (const vec_3& pos, const vec_3& target);

		const
		CPosition&  Pos (void) const;
		CPosition&  Pos (void);

		err_code Reset (void);  // sets this camera to default state of its components: camera position, target position and camera's 'look at';
		const
		CRotation&  Rotate (void) const;
		CRotation&  Rotate (void);
		const
		CTarget&    Target (void) const;
		CTarget&    Target (void);

	protected:
		CVirtCamera& operator = (const CVirtCamera&) = delete; CVirtCamera& operator = (CVirtCamera&&) = delete;
		CError m_error;

		camera::opers::CPosition m_pos;
		camera::opers::CRotation m_rotate;
		camera::opers::CTarget   m_target;
	};

}}}

typedef ex_ui::draw::open_gl::CVirtCamera TVirtCam;  TVirtCam& Get_virt_cam (void); // for test purposes one instance of the cam is enough;

#endif/*_VIRT_CAMERA_H_INCLUDED*/