#ifndef _GL_VIEWPORT_H_INCLUDED
#define _GL_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_vertex.h"

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif
#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

typedef
struct {
uint32_t cx = 0;
uint32_t cy = 0;
} t_size_u;

// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ; :: gettig the info of viewport;
// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ; :: z-buffer coord value mapping to window client area;
// https://stackoverflow.com/questions/59262874/how-can-i-use-screen-space-coordinates-directly-with-opengl :: good discussion of coord's precision;
// https://stackoverflow.com/questions/54058612/differing-floating-point-behaviour-between-uniform-and-constants-in-glsl ;
// https://stackoverflow.com/questions/37699310/convert-screen-coordinates-to-opengl-coordinates ;
// https://learnwebgl.brown37.net/08_projections/projections_ortho.html ;
// https://learnopengl.com/Getting-started/Coordinate-Systems ;
// https://community.khronos.org/t/floating-point-accuracy-in-glsl/62729/7 ;
// https://community.khronos.org/t/converting-window-coordinates-to-world-coordinates/16029/8 ;

namespace ex_ui { namespace draw { namespace open_gl {
	// https://en.wikipedia.org/wiki/Viewport ;
	// it is supposed the viewport dimensions are the same as target window client area is;
	class CViewPort : private no_copy {
	public:
		CViewPort (const uint32_t _u_width = 0, const uint32_t _u_height = 0); ~CViewPort (void);

		TError&   Error (void) const;
		t_size_u& Get (void)/* const*/; // returns the reference to 'unsigned' size structure, 'const' cannot be applied due to the compiler's error;
		t_size    Get (void) const;     // returns the current size of the viewport area; the standard/winapi size structure has fields of signed data type and that looks like not so good;
		err_code  Set (const uint32_t _u_width, const uint32_t _u_height); // sets the size of the viewport, left|top1 is assumed to be at '0|0';
		err_code  Set (const t_rect&);  // it is expected the input rectangle is in the target window client area coordinate system;

		bool Is_valid (void) const;     // it is assumed the width and height both do not equal to 0, otherwise 'false';

		vertex::CCoord ToPos (const long _x, const long _y) ;

	private:
		mutable
		CError   m_error;
		t_size_u m_size ;
	};

}}}

#endif/*_GL_VIEWPORT_H_INCLUDED*/