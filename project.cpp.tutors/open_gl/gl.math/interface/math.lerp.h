#ifndef _MATH_LERP_H_INCLUDED
#define _MATH_LERP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 14:13:55.980, UTC+4, Batumi, Friday;
	This is Ebo Pack math linear interpolation wrapper interface declaration file; 
*/
#include "math.defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	// https://en.wikipedia.org/wiki/Linear_interpolation >> time-based (game development);
	// https://english.stackexchange.com/questions/549250/why-is-linear-interpolation-called-lerp ; :-D
	/* 'lerp' violates all the rules of making an abbreviation;
	   'mix' in GLSL is much better;
	*/
	// https://en.wikipedia.org/wiki/Bilinear_interpolation >> image processing;
	// https://en.wikipedia.org/wiki/Spline_interpolation ;
	class c_interp {
	public:
		enum e_mode : int32_t {
			e_liner = 0x0, e_bounce, e_elastic
		};
		c_interp (void); c_interp (const c_interp&) = delete; c_interp (c_interp&&) = delete; ~c_interp (void) = default;
	private:
		c_interp& operator = (const c_interp&) = delete; c_interp& operator = (c_interp&&) = delete;
	};

}}}}

#endif/*_MATH_LERP_H_INCLUDED*/