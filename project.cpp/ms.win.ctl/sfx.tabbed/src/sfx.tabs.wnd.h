#ifndef _SFXTABSWND_H_INCLUDED
#define _SFXTABSWND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jul-2020 at 8:57:30p, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack Sfx tab control window interface declaration file.
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

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
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const t_size) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, t_rect*) override final;
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
#include "sfx.tabs.ctrl.h"
#include "sfx.tabs.fmt.h"

#include "shared.gen.syn.obj.h"

namespace ST_Ctrls { namespace _impl {

	using ex_ui::controls::CControlCrt  ;
	using ex_ui::controls::IControlEvent;

	using shared::sys_core::CSyncObject ;

	using ex_ui::draw::defs::IRenderer;

	using ST_Common::CToolTipHelper   ; typedef CToolTipHelper::ICallback TTipsCallback;
	using ST_Ctrls::format::CTabFormat;

	class CTabs_Wnd : public  ::ATL::CWindowImpl<CTabs_Wnd>, public TTipsCallback {
	                  typedef ::ATL::CWindowImpl<CTabs_Wnd> TWindow;
	private:
		CTabbed&         m_control;
		IRenderer*       m_parent ;
		CSyncObject      m_guard  ;
		TRndTile         m_bkg_rnd;
		CToolTipHelper   m__TTips ;      // tool tip helper object;
		CStringW         m__tips  ;
		
	public:
		 CTabs_Wnd (CTabbed&);
		~CTabs_Wnd (void);

	public:
		#define WM_ERASE     WM_ERASEBKGND
		#define WM_LBUTTONDN WM_LBUTTONDOWN

		DECLARE_WND_CLASS(_T("ST::controls::tabbed::wnd"));
		BEGIN_MSG_MAP(CTabs_Wnd)
			MESSAGE_HANDLER(WM_CREATE      , OnCreate     )
			MESSAGE_HANDLER(WM_DESTROY     , OnDestroy    )
			MESSAGE_HANDLER(WM_ERASE       , OnErase      )
			MESSAGE_HANDLER(WM_LBUTTONDN   , OnLButtonDn  )
			MESSAGE_HANDLER(WM_LBUTTONUP   , OnLButtonUp  )
			MESSAGE_HANDLER(WM_MOUSEMOVE   , OnMouseMove  )
			MESSAGE_HANDLER(WM_MOUSELEAVE  , OnMouseOut   )
			MESSAGE_HANDLER(WM_PAINT       , OnPaint      )
			NOTIFY_CODE_HANDLER(
				TTN_GETDISPINFO,   OnDispInfo
			)
		END_MSG_MAP()

	public:
		VOID    ParentRenderer (IRenderer* const);

	private:
		LRESULT OnCreate    (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnDestroy   (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnErase     (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnLButtonDn (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnLButtonUp (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnMouseMove (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnMouseOut  (UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnPaint     (UINT, WPARAM, LPARAM, BOOL&);
	private:
		LRESULT OnDispInfo  (INT , LPNMHDR lpHead, BOOL&);

	private:  //TTipsCallback
		LPCTSTR OnToolTipTextRequest(void) override;
	};

}}
#endif
#endif/*_SFXTABSWND_H_F2EE9082_4F3E_4968_B138_F7D2D87695C1_INCLUDED*/