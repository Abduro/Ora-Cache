#ifndef _COMMON_VIEW_H_INCLUDED
#define _COMMON_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2026 at 12:31:35.913, UTC+4, Batumi, Monday;
	This is virtual camera common GUI base view interface declaration file;
*/
#include "common.defs.h"

namespace test { namespace gui { namespace views { using namespace ::test::draw::defs;

	using CWebBrowser   = ::ex_ui::web::IE::CWebBrowser;
	using CLocator      = ::ex_ui::web::IE::urls::CLocator;
	using IWbEvtHandler = ::ex_ui::web::IE::defs::IWbEvtHandler;

	class CBase : public IWbEvtHandler {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void) = default;

		err_code Create (const HWND hParent, const rect_t& rect);
		err_code Destroy (void);

		TError& Error (void) const;

		err_code Open (_pc_sz _p_url);
		
		// IWbEvtHandler implementation;
		virtual err_code WbEvt_BeforeNavigate  (_pc_sz _p_url) override;
		virtual err_code WbEvt_DocumentComplete(_pc_sz _p_url, const bool _b_use_stream) override;
		virtual err_code WbEvt_OnMouseMessage  (const MSG&) override;

	protected:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError m_error;
		CWebBrowser m_browser;
	};

}}}

#endif/*_COMMON_VIEW_H_INCLUDED*/