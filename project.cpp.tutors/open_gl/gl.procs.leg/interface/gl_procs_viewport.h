#ifndef _GL_PROCS_VIEWPORT_H_INCLUDED
#define _GL_PROCS_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2026 at 17:44:00.482, UTC+4, Batumi, Saturday;
	This is OpenGL v.1.1 viewport related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace ver_1_1 {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport << sets view port size and position;
	// 
	class CViewport : public CBasic { typedef CBasic TBase;
	public:
		CViewport (const uint32_t _u_width = 0, const uint32_t _u_height = 0); CViewport (const CViewport&) = delete;
		CViewport (CViewport&&) = delete; ~CViewport (void) = default;
		const
		t_size_u& Get (void) const; // returns the reference to 'unsigned' size structure; (ro);
		static
		err_code  Get_Params (i_set_4&, CError&); // gets viewport params (from left to right): x-offset, y-offset, width and height of the viewport;

		float   Get_X (const int32_t _n_x) const; // converts x-coord value from screen to normalized one;
		float   Get_Y (const int32_t _n_x) const; // converts y-coord value from screen to normalized one;

		int32_t Get_X (const float _f_x) const;   // converts x-normalized value to screen coordinate;
		int32_t Get_Y (const float _f_y) const;   // converts y-normalized value to screen coordinate;

		static
		bool Is_valid (const t_size_u&, CError&);
		bool Is_valid (void) const; // it is assumed the width and height both do not equal to 0, otherwise 'false';

		// the conversion of screen coordinates is made for x|y values, z-coord has always 0.0f value;
		static
		err_code ToPos  (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, f_set_3& _pos_out, CError&);

	private:
		CViewport& operator = (const CViewport&) = delete; CViewport& operator = (CViewport&&) = delete;
		t_size_u m_size ;
		t_point  m_offset; // this is offset of viewport from top-left corner of the window client area; by default it is (0|0);
	};

}}}

#endif/*_GL_PROCS_VIEWPORT_H_INCLUDED*/