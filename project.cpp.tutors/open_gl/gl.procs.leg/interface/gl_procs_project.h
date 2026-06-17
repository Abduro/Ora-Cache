#ifndef _GL_PROCS_PROJECT_H_INCLUDED
#define _GL_PROCS_PROJECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 09:22:48.101, UTC+4, Batumi, Wednesday;
	This is OpenGL projection related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "utils\gl_procs_perspect.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace projection {
	
	using namespace ::shared::defs;
	using namespace ::open_gl::procs::ver_1_1;

	using f_mat_4x4 = ::open_gl::procs::f_mat_4x4;
	using var = ::open_gl::procs::utils::ver_1_1::c_converter;

	using namespace ::open_gl::math::defs;

	static _pc_sz p_err_neg_value = _T("#__inv_val: one of the planes is negative");
	static _pc_sz p_warn_no_draw  = _T("both of planes has negative value: nothing to draw;\n");

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

		static bool  Is_singular (const f_planes&, CError&); // checks for error: zNear and zFar have the same value (almost);
		static err_code Is_valid (const f_planes&, CError&); // checks for error: zNear or zFar is negative, but counterpart is positive;

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

namespace ver_1_1 {}
}}}

#endif/*_GL_PROCS_PROJECT_H_INCLUDED*/