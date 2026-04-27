#ifndef _MODEL_BASE_H_INCLUDED
#define _MODEL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 08:40:08.947, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' model base interface declaration file;
*/
#include "shared.defs.h"
#include "shared.preproc.h"

#include "gl_drawable.h" // for grid declaration;
#include "gl_viewport.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace models { using namespace shared::defs;

	using CGrid = ex_ui::draw::open_gl::view::CGrid;
	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	class CBase {
	public:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

		TError& Error (void) const;
		const
		CGrid& Grid (void) const;         // gets the reference to the background grid object; (ro)
		CGrid& Grid (void) ;              // gets the reference to the background grid object; (rw)
		const
		CViewPort& ViewPort (void) const; // gets the reference to view port object; (ro)
		CViewPort& ViewPort (void) ;      // gets the reference to view port object; (rw)

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError  m_error;
		CGrid   m_grid ;      // the grid is not implemented as a model yet;
		CViewPort m_v_port;
	};
}}}}

#endif/*_MODEL_BASE_H_INCLUDED*/