#ifndef _MATH_QUAT_H_INCLUDED
#define _MATH_QUAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 11:15:55.738, UTC+4, Batumi, Friday;
	This is Ebo Pack math quaternion wrapper interface declaration file; 
*/
#include "math.defs.h"
#include "math.vector.h"
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	// https://en.wikipedia.org/wiki/Quaternion ;
	// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation ;
	/* Quaternions are a four-dimensional number system used to represent and compute 3D rotations and orientations:
	(1) Structure: composed of a real scalar part (w) and a 3D vector part (x,y,z), often represented as a 4-tuple;
	(2) Rotation: used to rotate 3D vectors; A unit quaternion represents an axis-angle rotation, where the axis (x,y,z) is scaled by the sine of half the angle,
	              and (w) is the cosine of half the angle;
	(3) Advantages: quaternions avoid "gimbal lock," a common issue with Euler angles, and allow for smooth interpolation (Slerp: spherical linear interpolation) between rotations,
	                making them essential for 3D graphics, game engines (e.g., Unity, Unreal), robotics, and aerospace navigation.
	*/
	struct s_quat { // https://www.abbreviations.com/abbreviation/quaternion ;

		s_quat (void);
		s_quat (const vec_3&, const float _w);
		s_quat (const float _x, const float _y, const float _z, const float _w);

		s_quat&  Conjugate  (void);
		float    Get_length (void) const; // computes a normal of this quat;
		c_mat4x4 Get_mat4x4 (void) const; // returns matrix from quant of unit length;

		s_quat& Invert (void);
		s_quat& Normalize (void);         // converts to uinit quat;

		s_quat& Set (const float _x, const float _y, const float _z, const float _w);
		s_quat& Set (const vec_3& _axis, const float _angle); // the half of the angle;

		float   Sum2 (void) const;       // this is the sum of all the elements, each of which is raised to the power of 2;

		CString To_str (_pc_sz _p_format = _T("%.7f")) const;

		s_quat& operator = (const s_quat&);
		s_quat  operator * (const float) const;
		s_quat  operator * (const s_quat&) const;

		s_quat& operator <<(const float _w);
		s_quat& operator <<(const vec_3 _v);

		vec_3 v_3;
		float w;
	};
}}}}

#endif/*_MATH_QUAT_H_INCLUDED*/