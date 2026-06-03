#ifndef _GL_PROCS_FRUSTUM_H_INCLUDED
#define _GL_PROCS_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jun-2026 at 23:42:01.952, UTC+4, Batumi, Monday;
	This is OpenGL v.1.1 frustum related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace projection {
	using namespace open_gl::procs::ver_1_1;
	using namespace shared::defs;

	using namespace ::open_gl::math::defs;
	/* the excerpt from
	   The (left, bottom, zNear) and (right, top, zNear) parameters specify the points on the near clipping plane that are mapped to the lower-left and upper-right corners of the window,
	   respectively, assuming that the eye is located at (0,0,0).
	   that latter means the eye/camera resides at the centre of viewport space (f_rect);
	*/
	struct f_rect {
		float  f_left, f_top, f_right, f_bottom;

		f_rect (void);
		f_rect (const f_rect&);
		f_rect (const t_rect&);
		f_rect (const float _left, const float _top, const float _right, const float _bottom); ~f_rect (void) = default; f_rect (f_rect&&) = delete;

		void   Set (const f_rect&);
		void   Set (const t_rect&);  // the given input rectangle is checked for emptimess, and warning is traced if necessary;
		void   Set (const float _left, const float _top, const float _right, const float _bottom);

		bool   Is_empty (const float _threshold = f_epsilon) const;

		static
		_pc_sz To_str (const f_rect&);
		_pc_sz To_str (void) const;

		f_rect& operator = (const f_rect&);   f_rect& operator = (f_rect&&) = default;
		bool    operator <<(const t_rect&);   // returns 'false' if the input rectangle is empty;
	};

	struct d_rect {
		double  d_left, d_top, d_right, d_bottom;
		d_rect (void);
		d_rect (const d_rect&);
		d_rect (const double _left, const double _top, const double _right, const double _bottom); ~d_rect (void) = default;
		d_rect (const f_rect&);

		void  Set (const d_rect&);
		void  Set (const f_rect&);
		void  Set (const double _left, const double _top, const double _right, const double _bottom);

		d_rect& operator = (const d_rect&);
		d_rect& operator <<(const f_rect&);
		const
		d_rect& operator >>(f_rect&) const;
		/* print operation of this structure can be made through casting to f_rect structure;*/
	};
	/* the query to Google AI: can be near plane or far plane negative for frustum in opengl?
	Yes, the near and far plane distances in OpenGL can theoretically be negative, but only in specific, non-traditional rendering workflows.
	Traditional Perspective Projection (w > 0)
	(1) Positive values represent points in front of the camera.
	(2) Negative values would represent points behind the camera.
	(3) *important*: If a negative near or far plane, the vertices behind the camera would be incorrectly projected and clipped.
	*/
	struct f_planes {
		float f_near, f_far;

		f_planes (void);
		f_planes (const f_planes&);
		f_planes (const float _near, const float _far); ~f_planes (void) = default;

		static
		err_code Is_valid (const f_planes&, CError&);

		void Set (const f_planes&);
		void Set (const float _near, const float _far);

		static
		_pc_sz To_str (const f_planes&);
		_pc_sz To_str (void) const;

		f_planes& operator = (const f_planes&);
	};

	struct d_planes {
		double d_near, d_far;

		d_planes (void);
		d_planes (const d_planes&);
		d_planes (const double _near, const double _far); ~d_planes (void) = default;
		d_planes (const f_planes&);

		void Set (const d_planes&);
		void Set (const f_planes&);
		void Set (const double _near, const double _far);

		d_planes& operator = (const d_planes&);
		d_planes& operator <<(const f_planes&);
		const
		d_planes& operator >>(f_planes&) const;
		/* print operation of this structure can be made through casting to f_planes structure;*/
	};

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glfrustum ;
	class CFrustum : public CBasic { typedef CBasic TBase;
	public:
		CFrustum (void); CFrustum (const CFrustum&) = delete; CFrustum (CFrustum&&) = delete; ~CFrustum (void) = default;

		err_code Set (const f_rect& _clip, const f_planes&); // the sides values of d_rect must be in acceptable range [-1.0 ... 1.0];
		err_code Set (const t_rect& _clip, const f_planes&); // clip rectangle requires a conversion to normalized device space [-1.0 ... 1.0];

	private:
		CFrustum& operator = (const CFrustum&) = delete; CFrustum& operator = (CFrustum&&) = delete;
	};

}}}

#endif/*_GL_PROCS_FRUSTUM_H_INCLUDED*/