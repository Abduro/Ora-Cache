#ifndef _GL_DRAWABLE_H_INCLUDED
#define _GL_DRAWABLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:49:12.456, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface declaration file;
*/
#include "drawable\gl_grid_pers.h"
#include "drawable\gl_grid_layout.h"

namespace open_gl { namespace views { using namespace shared::defs;

	class CBkgnd : private ex_ui::draw::open_gl::no_copy {
	public:
		CBkgnd (void); ~CBkgnd (void);

		err_code Draw  (void);
		TError&  Error (void) const;

	private:
		CError m_error;
	};

	using namespace ex_ui::color;
	using e_rgba   = rgb::e_rgba;
	using e_object = ex_ui::draw::open_gl::CPipeline::e_object;

	// ToDo: it looks very like this class or its functionality needs to be moved to the rgb.color shared library project;
	class CClr_flt : public rgb::CFloat { typedef rgb::CFloat TBase;
	public:
		CClr_flt (void); ~CClr_flt (void);

		TError& Error (void) const;
#if (0) // this is intended for the grid object mainly, so grid persistent takes care about the color loading;
		err_code Get (const e_object); // loads the color for the draw pipeline component from the registry;
#endif
		// sets color as float value; if the value is out of range [0.0...1.0], the value is set to min or max value of the range;
		err_code Set (const float _r, const float _g, const float _b, const float _a = 1.0f);
		err_code Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a = 0xff);
		err_code Set (const CString&);         // sets color from given string; this method is used by grid persistent object;

	public:
		const
		rgb::CFloat&  operator ()(void) const; // gets the reference to the base class; (ro)
		rgb::CFloat&  operator ()(void) ;      // gets the reference to the base class; (rw)

	private:
		CError m_error;
	};

	using CPers = ::open_gl::views::grid::CPersistent;
	using CLayout = ::open_gl::views::grid::CLayout;
	// this grid classes uses the program, vertex array object and vertex array data which are managed by draw scene of the renderer object;
	class CGrid : private ex_ui::draw::open_gl::no_copy {
	public:
		CGrid (void); ~CGrid (void);

		const
		CClr_flt&  Clr (void) const;
		CClr_flt&  Clr (void) ;

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
		CError  m_error; CClr_flt m_color;
		CString m_name ; // the name must be unique among other grids, it is for saving/loading settings by persistent object;
		CPers   m_pers ;
		CLayout m_layout;
	};
}}

#endif/*_GL_DRAWABLE_H_INCLUDED*/