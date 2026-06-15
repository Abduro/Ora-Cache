#ifndef _VIEW_PORT_H_INCLUDED
#define _VIEW_PORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 11:45:00.815, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL viewport cache wrapper interface declaration file;
*/
#include "drawable.defs.h"
#include "gl_viewport.h"

namespace open_gl { namespace views { using namespace shared::defs;

	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	typedef ::std::map<HWND, CViewPort> view_cache_t; // the key is a surface window handle; the value is a viewport object of the client area of the window;

	class CViewports {
	public:
		 CViewports (void); CViewports (const CViewports&) = delete; CViewports (CViewports&&) = delete;
		~CViewports (void) = default;

		err_code Activate (const HWND _h_surface); // sets the viewport associated with given handle to be active, thus any object interested for viewport will be able to deal with;
		const
		CViewPort& Active (void) const; // gets the reference to the active viewport object; if no active viewport is set, the reference to fake object is returned;
		CViewPort& Active (void) ;      // gets the reference to the active viewport object; if no active viewport is set, the reference to fake object is returned;

		err_code Add (const HWND _h_surface); // new viewport is created for given window handle, client area rectangle is taken from surface; viewport being added is activated;
		TError&  Error (void) const;
		const
		CViewPort& Get (const HWND _h_surface) const; // gets the reference to viewport object associated with given surface handle; if not found the reference to fake object is returned; (ro)
		CViewPort& Get (const HWND _h_surface) ;      // gets the reference to viewport object associated with given surface handle; if not found the reference to fake object is returned; (rw)

		err_code Remove (const HWND _h_surface);      // removes a viewport from the cache by given surface handle;

	private:
		CViewports& operator = (const CViewports&) = delete; CViewports& operator = (CViewports&&) = delete;
		mutable
		CError  m_error;
		view_cache_t m_cached;
		HWND    m_active; // keeps HWND of surface window as the key for finding associated viewport object being active;
	};
}}

typedef ::open_gl::views::CViewports TViewPortCache; TViewPortCache& Get_ViewPorts (void);

#endif/*_VIEW_PORT_H_INCLUDED*/