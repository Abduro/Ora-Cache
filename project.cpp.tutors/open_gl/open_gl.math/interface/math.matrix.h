#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	class CMat2x2 {
	public:
		CMat2x2 (void); CMat2x2 (const CMat2x2&); CMat2x2 (CMat2x2&&); ~CMat2x2 (void);
		CMat2x2& operator = (const CMat2x2&);
		CMat2x2& operator = (CMat2x2&&);
	};

}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/