#ifndef _GL_VIEWPORT_H_INCLUDED
#define _GL_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_drawable.h"

#pragma region __refs_f
// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ; :: gettig the info of viewport;
// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ; :: z-buffer coord value mapping to window client area;
// https://stackoverflow.com/questions/59262874/how-can-i-use-screen-space-coordinates-directly-with-opengl :: good discussion of coord's precision;
#pragma endregion
namespace ex_ui { namespace draw { namespace open_gl {

	typedef ::std::array<float, 3u> t_set_3; // x|y|z;

	// https://en.wikipedia.org/wiki/Viewport ;
	// it is supposed the viewport dimensions are the same as target window client area is;
	class CViewPort : private no_copy {
	public:
		using CGrid = view::CGrid;
		CViewPort (const uint32_t _u_width = 0, const uint32_t _u_height = 0); ~CViewPort (void);

		TError&   Error (void) const;
		t_size_u& Get (void)/* const*/; // returns the reference to 'unsigned' size structure, 'const' cannot be applied due to the compiler's error;
		t_size    Get (void) const;     // returns the current size of the viewport area; the standard/winapi size structure has fields of signed data type and that looks like not so good;
		err_code  Set (const uint32_t _u_width, const uint32_t _u_height); // sets the size of the viewport, left|top1 is assumed to be at '0|0';
		err_code  Set (const t_rect&);  // it is expected the input rectangle is in the target window client area coordinate system;
		static
		bool Is_valid (const t_size_u&, CError&);
		bool Is_valid (void) const;     // it is assumed the width and height both do not equal to 0, otherwise 'false';
		const
		CGrid& Grid (void) const;
		CGrid& Grid (void) ;
		
		// the conversion for screen coordinates is made for x|y values, z-coord has always 0.0f value;
		static
		err_code ToPos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, t_set_3& _pos_out, CError&);
		err_code Update (void);         // updates the viewport grid layout;

		CViewPort& operator << (const t_rect&);

	private:
		mutable
		CError   m_error;
		t_size_u m_size ;
		CGrid    m_grid ;
	};

}}}

#endif/*_GL_VIEWPORT_H_INCLUDED*/