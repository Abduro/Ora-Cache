#ifndef _GL_CTX_RENDER_H_INCLUDED
#define _GL_CTX_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 23:38:47.041, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL draw renderer context interface declaration file;
*/
#include "gl_defs.h"
#include "gl_version.h" // gets the installed version of OpenGL 

namespace ex_ui { namespace draw { namespace open_gl { namespace context { using namespace shared::defs;

	using s_version = ex_ui::draw::open_gl::s_version;

	// to-do: this class must be reviewed: from one hand OpenGL version, from the other one, the version which is used by graphics context;
	class CPersistent { // for setting the version attributes that may be different by value in comparison with OpenGL installed on the OS;
	public:
		CPersistent (void) ; CPersistent (const CPersistent&) = delete; CPersistent (CPersistent&&) = delete; ~CPersistent (void) = default;

		TError&  Error (void) const;

		err_code Load (void);  // loads settings/options related to draw rendering context from the system registry;
		err_code Save (void);  // not used yet;

		const
		s_version& Prefer (void) const; // returns the reference to OpenGL version info preferable for work with;

		/*the version info is loaded from the system registry;*/
		bool  Use_core (void) const;

	private:
		CPersistent& operator = (const CPersistent&) = delete;
		CPersistent& operator = (CPersistent&&) = delete;
		CError    m_error;
		bool      m_use_core;
		s_version m_pref_ver;
	};

}}}}

typedef ex_ui::draw::open_gl::context::CPersistent TCtxPers; TCtxPers& Get_CtxPers (void);

#endif/*_GL_CTX_RENDER_H_INCLUDED*/