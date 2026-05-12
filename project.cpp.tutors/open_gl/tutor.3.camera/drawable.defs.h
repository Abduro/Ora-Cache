#ifndef __DRAWABLE_DEFS_H_INCLUDED
#define __DRAWABLE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 12:29:48.128, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object common declaration file;
*/
#include "shared.defs.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "shared.theme.h"

#include "math.matrix.h"
#include "runner.tpl.h"

namespace shared { namespace drawable { using namespace shared::defs;

	using CDelay = shared::runnable::CDelay;
	using CTplRunner = shared::runnable::threads::pool::CTplRunner;
}}

#include "gl_viewport.h"

namespace open_gl { namespace views {
	/* query: abbreviation for euclidean ; (Google AI) >> E or Euc ;
	   (1) ED : Euclidean Distance; https://en.wikipedia.org/wiki/Euclidean_distance ;
	   (2) EDM: Euclidean Distance Map or Matrix; https://en.wikipedia.org/wiki/Euclidean_distance_matrix ;
	            a matrix holds the numerical data of inter-point distances; computing is extensive and requires parallel processing on GPUs;
	            the app: coverting an image to grayscale; in geographics for finding paths; an obstacle detection in computer vision;
	   (3) EDT: Euclidean Distance Transform: common in image processing;
	            it is a function that assigns to each point in a space the distance to the nearest object by applying Pythagorean theorem to nearest pixels;
	            the app: widely used in computer vision for skeletonization, path planning, medical imaging, and object recognition; (the image must be grayscale)
	*/

	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	typedef ::std::map<HWND, CViewPort> view_cache_t; // the key is a surface window handle; the value is a viewport object of the client area of the window;

	class CCache {
	public:
		 CCache (void); CCache (const CCache&) = delete; CCache (CCache&&) = delete;
		~CCache (void) = default;

		err_code Activate (const HWND _h_surface); // sets the viewport associated with given handle to be active, thus any object interested for viewport will be able to deal with;
		const
		CViewPort& Active (void) const; // gets the reference to the active viewport object; if no active viewport is set, the reference to fake object is returned;
		CViewPort& Active (void) ;      // gets the reference to the active viewport object; if no active viewport is set, the reference to fake object is returned;

		err_code Add (const HWND _h_surface); // new viewport is created for given window handle, client area rectangle is taken from surface; viewport being added is activated;
		TError&  Error (void) const;
		const
		CViewPort& Get (const HWND _h_surface) const; // gets the reference to viewport object associated with given surface handle; if not found the reference to fake object is returned; (ro)
		CViewPort& Get (const HWND _h_surface) ;      // gets the reference to viewport object associated with given surface handle; if not found the reference to fake object is returned; (rw)

		err_code Remove (const HWND _h_surface);      // removes a viewport from the cache by given surface handle;

	private:
		CCache& operator = (const CCache&) = delete; CCache& operator = (CCache&&) = delete;
		mutable
		CError  m_error;
		view_cache_t m_cached;
		HWND    m_active; // keeps HWND of surface window as the key for finding associated viewport object being active;
	};

}}

typedef ::open_gl::views::CCache TViewPortCache; TViewPortCache& Get_ViewPorts (void); 

namespace open_gl { namespace views {
	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;

	class c_view_matrix : public c_mat4x4 { typedef c_mat4x4 base_t;
	public:
		c_view_matrix (void);
		// all shifting values in pixels;
		float& Shift_X (const int32_t _delta_x); // horz translation: shifting alone x-axis, positive value is the moving to the right, otherwise to the left;
		float& Shift_Y (const int32_t _delta_y); // vert translation: shifting alone y-axis, positive value is moving up, otherwise down;
		float& Shift_Z (const int32_t _wheel_value); // depth translation: shifting alone z-axis, positive value is moving toward a user, otherwise forward to screen; 

		const
		c_mat4x4& operator ()(void) const;
		c_mat4x4& operator ()(void) ;
	};

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
}}

#endif/*__DRAWABLE_DEFS_H_INCLUDED*/