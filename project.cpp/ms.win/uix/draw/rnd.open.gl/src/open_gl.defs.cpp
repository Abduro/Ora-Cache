/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Aug-2025 at 23:58:27.843, (UTC+4) Batumi, Friday;
	This is Ebo Pack OpenGL based draw renderer generic definitions' implementation file;
*/
#include "open_gl.defs.h"

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl { void __warning_lnk_4221(void) {}

	class CFake_Wnd : public ::ATL::CWindowImpl<CFake_Wnd> { typedef ::ATL::CWindowImpl<CFake_Wnd> TBase;
	public:
		 CFake_Wnd (void) : m_h_dc(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

			TBase::Create(HWND_MESSAGE);

			if (false == TBase::IsWindow())
				this->m_error.Last();
			else {
				this->m_error << __s_ok;
				this->m_h_dc = TBase::GetDC();
			}
		 }
		 CFake_Wnd (const CFake_Wnd&) = delete; CFake_Wnd (CFake_Wnd&&) = delete;
		~CFake_Wnd (void) {
		
			if (nullptr != this->m_h_dc) {
				TBase::ReleaseDC(this->m_h_dc); this->m_h_dc = nullptr;
			}

			if (TBase::IsWindow())
				TBase::DestroyWindow();
		}
	public:
		DECLARE_EMPTY_MSG_MAP();
		const
		HDC&     Ctx   (void) const { return this->m_h_dc; }
		TError&  Error (void) const { return this->m_error; }

		operator const HDC& (void) const { return this->Ctx(); }

	private:
		CError  m_error;
		HDC     m_h_dc ;
	};

}}}}
using namespace ex_ui::draw::open_gl::_impl;

CVersion:: CVersion (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	CFake_Wnd fk_wnd;
	if (fk_wnd.Error())
		this->m_error = fk_wnd.Error();
	else {
		this->m_error << __s_ok;
	}
}

CVersion::~CVersion (void) {
}

TError& CVersion::Error (void) const { return this->m_error; }