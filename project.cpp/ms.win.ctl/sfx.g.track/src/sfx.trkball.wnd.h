#ifndef _SFX_TRKBALL_WND_H_INCLUDED
#define _SFX_TRKBALL_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 21:38:59.386, UTC+4, Batumi, Monday;
	This is Ebo Pack thackball control window interface deckaration file;
*/
#include "sfx.trkball.inc.h"
namespace ex_ui { namespace controls { namespace sfx { namespace track { class CControl;

	using namespace ex_ui::controls::sfx;
	using namespace ex_ui::message::handlers;

	using IBtnsEvtSink = ex_ui::message::handlers::mouse::buttons::IBtnEventSink;
	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;

	using ex_ui::popup::CWndBase;
	using CEvent = ex_ui::message::handlers::mouse::buttons::CEvent;

	class CWnd : public CWndBase, IDrawEvtSink, ILifeEvtSink, IFormEvtSink, IBtnsEvtSink { typedef CWndBase TWindow;
	public:
		 CWnd (CControl&) ; CWnd (void) = delete; CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void) ;

#pragma region __msg_handler_callbacks__
	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase   (const HDC _dev_ctx) override final;
		err_code IEvtDraw_OnPaint   (const w_param, const l_param) override final;

	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const t_size) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, t_rect*) override final;

	private: // IBtnsEvtSink override;
		err_code IEvtButton_OnReceive(const CEvent&) override final;

	private:  // ILifeEvtSink override(s);
		err_code IEvtLife_OnCreate  (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy (const w_param, const l_param) override final;
#pragma endregion
	private:
		CWnd& operator = (const CWnd&) = delete;
		CWnd& operator = (CWnd&&) = delete;
	private:
		CControl& m_ctrl;
	};

}}}}

#endif/*_SFX_TRKBALL_WND_H_INCLUDED*/