#ifndef _WND_BASE_H_INCLUDED
#define _WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Oct-2021 at 10:11:04.4118880 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window adapter base interface declaration file.
*/
#include <atlbase.h>
#include <atlwin.h>
#include <set>

#include "sys.error.h"
#include "handlers.h"

#include "shared.types.h"

namespace ex_ui { namespace popup {

	using namespace shared::types;

	// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features ;
	// https://www.equestionanswers.com/vcpp/client-non-client-area.php ;

	using namespace ex_ui::message::handlers;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	class CWndBase : public ::ATL::CWindowImpl<CWndBase> {
	                typedef ::ATL::CWindowImpl<CWndBase> TWindow;
	public:
		 CWndBase (_pc_sz _p_cls_name = nullptr);
		 CWndBase (const CWndBase&) = delete;
		 CWndBase (CWndBase&&) = delete;
		~CWndBase (void);

	public:
		DECLARE_WND_CLASS(__CLASS__);

		BEGIN_MSG_MAP(CWndBase)
			CHAIN_MSG_MAP_MEMBER(m_handlers);
		END_MSG_MAP()

	public:
		TError&  Error (void) const;
		const
		TMsgHandlers& Handlers(void) const;
		TMsgHandlers& Handlers(void) ;

	protected:
		TMsgHandlers  m_handlers; // message handler set is eccential for an operating window properly; thus handlers must exist always;
		CError  m_error;
	};
}}

typedef ex_ui::popup::CWndBase TWndBase;

#endif/*_WND_BASE_H_INCLUDED*/