#ifndef _GL_PROCS_BASIC_H_INCLUDED
#define _GL_PROCS_BASIC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 20:04:02.817, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface declaration file;
*/
#include "shared.defs.h"
#include <gl/gl.h>       // the headers' include order is important: windows.h must go first;
#include <gl/glu.h>
#include "gl_error.h"
/**important*:
   all functions related to legacy fixed pipeline of the OpenGL ver 1.1 does not require loading its addresses,
   because it is expected the libraries referenced below contain those functions;
*/
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
/* taking into account the fact that these tutorials are implemented under MS Windows and OpenGL ver 1.1 is used,
   the most of the reference is made to Microsoft documentation related to using OpenGL:
   https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-reference ;
*/
#include "shared.preproc.h"
#include "shared.dbg.h"

namespace open_gl { namespace math { namespace defs {
	/* query: what has Pi value in math (to Google AI);
	   The value of Pi  is a mathematical constant defined as the ratio of a circle’s circumference to its diameter. It is approximately equal to 3.14159;
	   Numerical Value:
	   For everyday calculations, it is frequently rounded to 3.14; a more precise fraction, it is commonly estimated as 22/7: ~3.142857143;
	   In C and C++, the float data type typically provides 6 to 9 significant decimal digits of precision.
	   Most implementations guarantee that at least 6 digits can be stored and retrieved without information loss.
	*/
	// https://stackoverflow.com/questions/39834989/what-are-the-maximum-number-of-base-10-digits-in-the-fractional-part-of-a-floati ;

	static const float  f_pi      =  3.142857143f;
	static const float  deg_2_rad =  0.017460317f;  //   f_pi / 180.0f;
	static const float  rad_2_deg = 57.27272727f;   // 180.0f / f_pi;
	static const float  f_epsilon =  0.00001f;
}
	// https://stackoverflow.com/questions/46189910/weird-method-to-check-if-a-float-number-is-negative ;

	static bool  Is_negative (const float _value) { // this function does not care of -0 and +0;
		_value;
#if (1)
		static char buffer[2] = {0};
		::snprintf(buffer, sizeof(buffer), "%f", _value);
#else
		return false == (static_cast<int>(_value + 1) > 0);
#endif
		return buffer[0] == '-';
	}
}}
namespace open_gl { namespace procs {
	/* the query to Goodle AI: can std::array::data() return nullptr?
	Yes, std::array::data() can return nullptr, but only if the array is empty (i.e., its size is 0).
	For any array with a size greater than 0, it is guaranteed to return a valid, non-null pointer to the underlying contiguous memory storage.
	*/
	typedef ::std::array<float  , 0x10u> f_mat_4x4; // for matrix 4x4 entries' array;
	typedef ::std::array<float  , 0x03u> f_set_3;   // x|y|z;
	typedef ::std::array<int32_t, 0x04u> i_set_4;   // for example to query viewport params: x, y of Offset from top-left corner, followed by its width and height;

	struct t_size_u {
		uint32_t cx, cy;
		t_size_u (void) : cx(0), cy(0){}
		t_size_u (const uint32_t _cx,  const uint32_t _cy) : cx(_cx), cy(_cy) {}
		t_size_u (const t_size_u& _src) : t_size_u() { *this = _src; }
		t_size_u& operator = (const t_size_u& _src) { this->cx = _src.cx; this->cy = _src.cy; return *this; }
	};
namespace ver_1_1 {

	using namespace shared::defs;
	using namespace ATL;

	using ::ex_ui::draw::open_gl::CError_ex;
	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

//	static _pc_sz p_err_inv_oper  = _T("#__e_inv_oper: called between glBegin() and glEnd()"); // this is the silly error message that appears in case when no current context is set;
	static _pc_sz p_err_inv_oper  = _T("#__e_inv_oper: current rendering context is not set"); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
	static _pc_sz p_err_unk_code  = _T("#__e_undef: error code 0x%04x (%d)");
	static _pc_sz p_err_inv_enum  = _T("#__e_inv_enum: '_prop_id' 0x%04x (%d) is not accepted");
	static _pc_sz p_err_unk_param = _T("#__e_inv_enum: '_param_id' 0x%04x (%d) is unknown");

	class CBasic {
	public:
		TError&  Error (void) const;
		PROC     Get (_pc_sz _p_fun_name); // https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;

	protected:
		CBasic (void); CBasic (const CBasic&) = delete; CBasic (CBasic&&) = delete; ~CBasic (void) = default;
		mutable
		CError  m_error;
	private:
		CBasic& operator = (const CBasic&) = delete; CBasic& operator = (CBasic&&) = delete;
	};

}}}

#endif/*_GL_PROCS_BASIC_H_INCLUDED*/