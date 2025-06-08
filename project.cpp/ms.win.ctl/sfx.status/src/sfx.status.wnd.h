#ifndef _SFXSTATUSWND_H_12053EA1_96E6_44E2_AC55_3C13F2D9930E_INCLUDED
#define _SFXSTATUSWND_H_12053EA1_96E6_44E2_AC55_3C13F2D9930E_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 10:06:48a, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control window interface declaration file.
*/
#include "sfx.status.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace status { class CControl;

	using namespace ex_ui::controls::sfx;
	using namespace ex_ui::message::handlers;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;
	using ex_ui::popup::CWndBase;

	class CWnd : public CWndBase, IDrawEvtSink, ILifeEvtSink, IFormEvtSink { typedef CWndBase TWindow;
	public:
		 CWnd (CControl&) ; CWnd (void) = delete; CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void) ;

#ifndef __WND_CLS_CHILD__
#define __WND_CLS_CHILD__
	//	DECLARE_WND_SUPERCLASS(TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), _T("CWndBase"));
#endif

#pragma region __msg_handler_callbacks__
	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase   (const HDC _dev_ctx) override final;
		err_code IEvtDraw_OnPaint   (const w_param, const l_param) override final;

	private:  // ILifeEvtSink override(s);
		err_code IEvtLife_OnCreate  (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy (const w_param, const l_param) override final;

	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const SIZE) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, LPRECT) override final;
#pragma endregion
	private:
		CWnd& operator = (const CWnd&) = delete;
		CWnd& operator = (CWnd&&) = delete;
	private:
		CControl& m_ctrl;
	};

}}}}

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