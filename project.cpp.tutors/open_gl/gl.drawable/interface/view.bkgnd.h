#ifndef _DRAWABLE_BKGND_H_INCLUDED
#define _DRAWABLE_BKGND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jun-2026 at 12:09:38.0046666, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' view background interface declaration file;
*/
#include "drawable.defs.h"

namespace open_gl { namespace views { using namespace shared::defs;

	/* the query to Google AI: can background be a shape or it is just a color in drawing by opengl?
	   In OpenGL, the background is strictly set as a flat color using the glClearColor function, rather than an interactive shape.
	   (1) The 'True' Background (Solid Color):
	       You define a background color using an RGBA (Red, Green, Blue, Alpha) value. This clears the entire screen or viewport.
	    a) Function: glClearColor(red, green, blue, alpha);
	    b) Execution: glClear(GL_COLOR_BUFFER_BIT);
	    c) Note: Values range from 0.0 to 1.0.
	   (2) The 'Shape' Background:
	       To use a shape (like a colored rectangle, gradient, or image) as a background, you render it as a 2D or 3D object filling the screen coordinates.
	       Process:
	    a) Disable depth testing so the shape stays in the back;
	    b) Draw a full-screen quad (rectangle) using your desired shape coordinates;
	    c) Apply a texture or color to this quad;
	    d) Re-enable depth testing and draw your main scene on top of it.
	*/
	class CBkgnd {
	public:
		CBkgnd (void); CBkgnd (const CBkgnd&) = delete; CBkgnd (CBkgnd&&) = delete; ~CBkgnd (void) = default;

		err_code Draw (void);     // draws background by using OpenGL v.1.1 API; sets solid color for the background;
		err_code Draw_Arb (void); // draws background by using OpenGL above ver;

		TError&  Error (void) const;

	private:
		CBkgnd&  operator = (const CBkgnd&) = delete; CBkgnd& operator = (CBkgnd&&) = delete;
		CError m_error;
	};


}}

#endif/*_DRAWABLE_BKGND_H_INCLUDED*/