#ifndef _OPEN_GL_TUTOR_3_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_3_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 02:53:28.276, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to OpenGL tutorials' camera project on 27-Nov-2025 at 00:36:54.670, UTC+4, Batumi, Thursday;
*/
#include "gl_context.h"
#include "shared.wnd.fake.h"
#include "shared.wnd.base.h" 

namespace ex_ui { namespace draw { namespace open_gl { namespace camera {

	using namespace shared::defs;
	using namespace shared::types;

	using namespace ex_ui::popup;

	using CFakeWnd = ex_ui::popup::CMsgWnd;

	class CWnd : public ex_ui::popup::CWndBase { typedef ex_ui::popup::CWndBase TBase; using CDevice = context::CDevice;
	public:
		 CWnd (void);
		~CWnd (void);

		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final;

		err_code Create (const HWND _h_parent, const t_rect&, const bool _b_visible = true);
		err_code Destroy (void);
		err_code PostCreate (void);

	protected:
		CFakeWnd  m_fak_wnd; // message-only window (aka fake) is created in its constructor;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_3_WND_H_INCLUDED*/