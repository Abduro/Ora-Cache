#ifndef _GL_PROCS_VSYNC_H_INCLUDED
#define _GL_PROCS_VSYNC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 09:59:53.565, UTC+4, Batumi, Wednesday;
	This is OpenGL ver.1.1 buffers' swap wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace utils { namespace ver_1_1 {

	using namespace ::shared::defs;
	using namespace ::open_gl::procs::ver_1_1;

	class CVSync : public CBasic { typedef CBasic TBase;

	typedef int32_t (__stdcall *pfn_GetSwapInterval)(void);  // https://registry.khronos.org/OpenGL/extensions/EXT/WGL_EXT_swap_control.txt ;
	typedef int32_t (__stdcall *pfn_SetSwapInterval)(int32_t _n_value);

	public:
		CVSync (void); CVSync (const CVSync&) = delete; CVSync (CVSync&&) = delete; ~CVSync (void) = default;

		int32_t  Get (void); // gets swap interval numbers between draw frames (aka VSync); error object is set if an error occurs;
		err_code Set (const uint32_t _intervals); // sets the input intervals' count;

	private:
		CVSync& operator = (const CVSync&) = delete; CVSync& operator = (CVSync&&) = delete;
	};

}}}}

#endif/*_GL_PROCS_VSYNC_H_INCLUDED*/