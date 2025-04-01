#ifndef _WIN_GUI_WND_H_INCLUDED
#define _WIN_GUI_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 09:57:46.7960802, UTC+7, Novosibirsk, Tuesday;
	This is window popup test app main window interface declaration file;
*/
#include "wnd.base.h"

namespace ebo { namespace boo { namespace gui {

	using ex_ui::popup::CWndBase;

	using namespace ex_ui::message::handlers;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;
	using ISysEvtSink  = ex_ui::message::handlers::IMsgSysEventSink;

	class CWindow : public CWndBase, IDrawEvtSink, ILifeEvtSink, ISysEvtSink, IFormEvtSink { typedef CWndBase TBase;
	public:
		 CWindow (void) ;
		 CWindow (const CWindow&) = delete;
		 CWindow (CWindow&&) = delete;
		~CWindow (void) ;

	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase   (const HDC _dev_ctx) override final;

	private:  // ILifeEvtSink override(s);
		err_code IEvtLife_OnClose   (const w_param, const l_param) override final; // reminder: if result is __s_ok, this window is still open;
		err_code IEvtLife_OnCreate  (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy (const w_param, const l_param) override final;

	private: // ISysEvtSink override(s);
		err_code IEvtSys_OnSysCmd   (const w_param, const l_param) override final; // reminder: if result is __s_ok, this process will be ended up;

	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const SIZE) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, LPRECT) override final;

	private:
		CWindow& operator = (const CWindow&) = delete;
		CWindow& operator = (CWindow&&) = delete;
	};

}}}

#endif/*_WIN_GUI_WND_H_INCLUDED*/