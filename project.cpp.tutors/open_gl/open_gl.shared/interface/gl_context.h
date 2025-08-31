#ifndef _GL_CONTEXT_H_INCLUDED
#define _GL_CONTEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_error.h"

namespace ex_ui { namespace draw { namespace open_gl {

	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

namespace context {

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		 TErr_ex& Error (void) const;

	private:
		 CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	protected:
		 CError_ex m_error;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	// excerpt: ...creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc... ;
	class CDevice : public CBase {
	public:
		 CDevice (void);
		~CDevice (void);

		err_code Create (const HWND); // creates the rendering context that is compatible with input window device context;
		err_code Destroy(void);

	private:
		HDC    m_dc_src ; // this is the source device context from which the device renderer is created;
		HGLRC  m_drw_ctx; // rendering context that is compatible with regular GDI;
		HWND   m_target ; // the target window handle, it owns the source device context;
	};

}}}

}

#endif/*_GL_CONTEXT_H_INCLUDED*/