#ifndef _GL_VERTEX_H_INCLUDED
#define _GL_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vertex {

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
}

	class CVertex : public vertex::CBase { typedef vertex::CBase TBase;
	public:
		 CVertex (void) ;  CVertex (const CVertex&) = delete; CVertex (CVertex&&) = delete;
		~CVertex (void) ;

		 const
		 procs::CProg& Cache (void) const;
		 procs::CProg& Cache (void) ;

	private:
		 CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;

		 procs::CProg  m_fn_cache;
	};

}}}

#endif/*_GL_VERTEX_H_INCLUDED*/