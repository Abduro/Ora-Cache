#ifndef _SFXSTATUSWND_H_12053EA1_96E6_44E2_AC55_3C13F2D9930E_INCLUDED
#define _SFXSTATUSWND_H_12053EA1_96E6_44E2_AC55_3C13F2D9930E_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 10:06:48a, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control window interface declaration file.
*/
#if (0)
#include "shared.uix.gdi.draw.defs.h"
#include "shared.uix.gdi.renderer.h"
#include "shared.uix.ctrl.base.wnd.h"
#include "sfx.tips.h"
#include "sfx.status.ctrl.h"
#include "sfx.status.fmt.h"
#include "shared.gen.syn.obj.h"

namespace ST_Ctrls { namespace _impl {

	using ex_ui::controls::CControlCrt;
	using ex_ui::controls::IControlEvent;

	using shared::sys_core::CSyncObject;

	using ex_ui::draw::defs::IRenderer;

	using ex_ui::controls::CControlBaseWnd; typedef CControlBaseWnd TCtrlWnd;
	using ST_Common::CToolTipHelper; typedef CToolTipHelper::ICallback TTipsCallback;
	using ST_Ctrls::format::CStatus; typedef CStatus TStatusFmt;

	class CStatus_Wnd : public TCtrlWnd, public TTipsCallback {
#ifndef __WND_CLS_CHILD__
#define __WND_CLS_CHILD__
		DECLARE_WND_CLASS(_T("ST::controls::sta::wnd"));
#endif
	protected:
		CStatusBar&      m_control;
		IRenderer*       m_parent ;
		CControlCrt      m_crt;
		TCtrlRender_Ex   m_rnd;
		CToolTipHelper   m__TTips ;      // tool tip helper object;
		CStringW         m__tips  ;
		CSyncObject      m_guard  ;
		HIMAGELIST       m_images ;

	public:	
		 CStatus_Wnd (CStatusBar&, IControlEvent&);
		~CStatus_Wnd (void);

	public:
	
		HRESULT    Format (const TStatusFmt&);
		VOID       ParentRenderer (IRenderer* const);

	private:
#pragma warning(disable: 4481)
		LRESULT OnErase (UINT, WPARAM, LPARAM, BOOL&) override sealed;
#pragma warning(disable: 4481)
	private:  //TTipsCallback
		LPCTSTR OnToolTipTextRequest(void) override;
	};
}}
#endif
#endif/*_SFXSTATUSWND_H_12053EA1_96E6_44E2_AC55_3C13F2D9930E_INCLUDED*/