#ifndef _GL_DRAWABLE_H_INCLUDED
#define _GL_DRAWABLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:49:12.456, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface declaration file;
*/
#include "drawable.defs.h"
#include "grid\grid.pers.h"
#include "grid\grid.layout.h"

namespace open_gl { namespace views { using namespace shared::defs;

	using CPers = ::open_gl::views::grid::CPersistent;
	using CLayout = ::open_gl::views::grid::CLayout;
	using Color_f = ::ex_ui::color::rgb::CFloat;
	// this grid classes uses the program, vertex array object and vertex array data which are managed by draw scene of the renderer object;
	/* the query to Google AI: grid is a shape of lines or not opengl?
	Yes. A grid can be defined as a parametric shape formed by intersecting horizontal and vertical lines.
	It is often used as a visual baseline (like a floor plane in 3D modeling software or game engines) to help spatial perception.
	*/
	class CGrid : private ex_ui::draw::open_gl::no_copy {
	public:
		CGrid (void); ~CGrid (void);

		const
		Color_f& Clr (void) const;
		Color_f& Clr (void) ;

		err_code Create  (void);
		err_code Destroy (void);

		err_code Draw  (void);
		TError&  Error (void) const;
		const
		CLayout& Layout (void) const;
		CLayout& Layout (void);

		const
		CString& Name (void) const;
		bool     Name (_pc_sz);      // sets the grid object name; returns 'true' in case of name change;
		const
		CPers&   Pers (void) const;
		CPers&   Pers (void);

	private:
		CError   m_error; Color_f m_color;
		CString  m_name ; // the name must be unique among other grids, it is for saving/loading settings by persistent object;
		CPers    m_pers ;
		CLayout  m_layout;
	};
}}

#endif/*_GL_DRAWABLE_H_INCLUDED*/