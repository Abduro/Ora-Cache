#ifndef _CAMERA_BASE_H_INCLUDED
#define _CAMERA_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-May-2026 at 01:26:29.672, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' virtual camera base interface declaration file;
*/
#include "shared.defs.h"
#include "shared.preproc.h"

namespace open_gl { using namespace shared::defs;
namespace camera {
	/* query: using union c++ (Google AI);
	Modern Alternative: std::variant () is introduced in C++17 (https://en.cppreference.com/w/cpp/utility/variant);
	but it very looks like that is stolen from boost, the boost created 'variant' before 2007 year;
	*/
	struct s_angles {
		union {
			float _x, _y, _z;
		};
		float _degrees[3];

		s_angles (const float _f_x = 0.0f, const float _f_y = 0.0f, const float _f_z = 0.0f) : _degrees{_f_x, _f_y, _f_z} {}

		const float& head  (void) const { return this->_x; } float& head (void)  { return this->_x; }
		const float& pitch (void) const { return this->_y; } float& pitch (void) { return this->_y; }
		const float& roll  (void) const { return this->_z; } float& roll (void)  { return this->_z; }

		CString To_str (void) const {
			static _pc_sz p_pat = _T("head=%.7f;pitch=%.7f;roll=%.7f");
			CString cs_out; cs_out.Format(p_pat, this->head(), this->pitch(), this->roll());
			return  cs_out;
		}
	};

	struct s_pos {
		union {
			float _x, _y, _z;
		};
		float _coords[3];

		s_pos (const float _f_x = 0.0f, const float _f_y = 0.0f, const float _f_z = 0.0f) : _coords{_f_x, _f_y, _f_z} {}

		CString To_str (void) const {
			static _pc_sz p_pat = _T("x=%.7f;y=%.7f;z=%.7f");
			CString cs_out; cs_out.Format(p_pat, this->_x, this->_y, this->_z);
			return  cs_out;
		}
	};
}
	class CCamera {
	public:
		using s_angles = ::open_gl::camera::s_angles;
		using s_pos = ::open_gl::camera::s_pos;
		CCamera (void); CCamera (const CCamera&) = delete; CCamera (CCamera&&) = delete; ~CCamera (void) = default;
		const
		s_angles& Angles (void) const;
		s_angles& Angles (void) ;

		TError&  Error (void) const;
		const
		s_pos&   Pos (void) const;
		s_pos&   Pos (void) ;

	private:
		CCamera& operator = (const CCamera&) = delete; CCamera& operator = (CCamera&&) = delete;
		mutable
		CError   m_error;
		s_pos    m_pos;
		s_angles m_angles;
	};
}

#endif/*_CAMERA_BASE_H_INCLUDED*/