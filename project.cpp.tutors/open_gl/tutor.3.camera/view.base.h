#ifndef _VIEW_BASE_H_INCLUDED
#define _VIEW_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 02:01:31.446, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' view base interface declaration file;
*/
#include "shared.defs.h"
#include "shared.preproc.h"
#include "gl_context.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace views { using namespace shared::defs;

	using CDevice   = ex_ui::draw::open_gl::context::CDevice;
	using CGraphs   = ex_ui::draw::open_gl::CGraphics;
	using CSelector = ex_ui::draw::open_gl::context::CSelector;

	// this class has both contexts: device context and draw rendering context;
	class CBase {
	public:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

		err_code Create (const HWND);   // creates device context and rendering conttext from given window handle (draw surface);
		err_code Destroy (void);        // it is assumed the drafter worker thread is *not* running at time of calling this proc;
		const
		CDevice& Device (void) const;   // gets the reference to device context; (ro)
		CDevice& Device (void) ;        // gets the reference to device context; (rw)

		TError&  Error (void) const;

		const
		CGraphs& Graphs (void) const; // gets the reference to draw rendering context; {ro)
		CGraphs& Graphs (void) ;      // gets the reference to draw rendering context; {rw)

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError   m_error;
		CDevice  m_device;
		CGraphs  m_graphs;
	};

}}}}

#endif/*_VIEW_BASE_H_INCLUDED*/