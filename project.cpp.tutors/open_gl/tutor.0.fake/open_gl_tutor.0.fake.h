#ifndef _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:16:27.485, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL fake (message-only) window interface declaration file;
*/
#include "open_gl_tutor.0.defs.h"

namespace ex_ui { namespace draw { namespace open_gl {  namespace fake {

	using namespace ex_ui::draw::open_gl;

	class CWnd : public ::ATL::CWindowImpl<CWnd> { typedef ::ATL::CWindowImpl<CWnd> TWindow;
	public:
		 CWnd (void); CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void);

		 static
		 const uint32_t u_style = CS_DBLCLKS | CS_OWNDC; // cs_owndc is important for creating open_gl window content;

		 DECLARE_WND_CLASS_EX(_T("open_gl::fake::CWnd"), u_style, COLOR_ACTIVECAPTION);
		 DECLARE_EMPTY_MSG_MAP();

		 TError& Error (void) const;
		 bool    Is_valid (void) const;

		 const
		 HDC&    Get_ctx (void) const; // gets the reference to device context; read-only;
		 HDC&    Get_ctx (void) ;

		 operator const HDC& (void) const;

	private:
		 CWnd& operator = (const CWnd&) = delete; CWnd& operator = (CWnd&&) = delete;

		 mutable
		 CError  m_error;
		 HDC     m_h_dc ;
	};

}}}}

typedef ex_ui::draw::open_gl::fake::CWnd  TFakeWnd;

#endif/*_OPEN_GL_TUTOR_0_FAKE_H_INCLUDED*/