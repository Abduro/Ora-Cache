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

	using CFont = ex_ui::draw::CFont;

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
		CFont     m_font;
		CFont     m_font_vert;  // ToDo: it would be better to re-create the one font if the tabs' orientation is changed;
	};

}}}}

#endif/*_SFXTABSWND_H_F2EE9082_4F3E_4968_B138_F7D2D87695C1_INCLUDED*/