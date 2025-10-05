#ifndef _SHARED_WND_FAKE_H_INCLUDED
#define _SHARED_WND_FAKE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Oct-2025 at 10:17:19.053, (UTC+4), Batumi, Sunday;
	This is Ebo Pack shared message-only (i.e. fake) window interface declaration file; 
*/
#include "shared.defs.h"

namespace ex_ui { namespace popup { using namespace shared::defs;
	// creates the 'message' window in its constructor; and destroys the window in its destructor;
	class CMsgWnd : public ::ATL::CWindowImpl<CMsgWnd> { typedef ::ATL::CWindowImpl<CMsgWnd> TWindow;
	public:
		 CMsgWnd (void); CMsgWnd (const CMsgWnd&) = delete; CMsgWnd (CMsgWnd&&) = delete;
		~CMsgWnd (void);

		 static
		 const uint32_t u_style = CS_DBLCLKS | CS_OWNDC; // cs_owndc is important for creating open_gl window content;

		 DECLARE_WND_CLASS_EX(_T("shared::fake::CWnd"), u_style, COLOR_ACTIVECAPTION);
		 DECLARE_EMPTY_MSG_MAP();

		 TError& Error (void) const;
		 bool    Is_valid (void) const;

		 const
		 HDC&    Get_ctx (void) const; // gets the reference to device context; read-only; (ro);
		 HDC&    Get_ctx (void) ;      // gets the reference to device context; read-write; (rw);

		 operator const HDC& (void) const;

	private:
		 CMsgWnd& operator = (const CMsgWnd&) = delete; CMsgWnd& operator = (CMsgWnd&&) = delete;
	protected:
		 mutable
		 CError  m_error;
		 HDC     m_h_dc ;
	};

}}

#endif/*_SHARED_WND_FAKE_H_INCLUDED*/