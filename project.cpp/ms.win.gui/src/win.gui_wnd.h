#ifndef _WIN_GUI_WND_H_INCLUDED
#define _WIN_GUI_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 09:57:46.7960802, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack draw renderer test app main window interface declaration file;
*/
#include "win.gui.inc.h"

#include "direct_x.surface.h"
#include "direct_x.wrap.h"

#include "ebo.sha.gui.theme.h"

namespace ebo { namespace boo { namespace gui {
#if (0)
#ifndef _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_NO_AUTOMATIC_NAMESPACE // https://learn.microsoft.com/en-us/cpp/atl/reference/compiler-options-macros ;
#endif
#endif
	using ex_ui::popup::CWndBase;
	using ebo::boo::gui::render::CSurface;

	using namespace ex_ui::message::handlers;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;
	using ISysEvtSink  = ex_ui::message::handlers::IMsgSysEventSink;

	class CWnd : public CWndBase, IDrawEvtSink, ILifeEvtSink, ISysEvtSink, IFormEvtSink { typedef CWndBase TBase;
	public:
		 CWnd (_pc_sz _p_cls_name = nullptr) ;
		 CWnd (const CWnd&) = delete;
		 CWnd (CWnd&&) = delete;
		~CWnd (void) ;

		// DECLARE_WND_CLASS(TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__)); // doesn't work and shouldn't;
		// https://learn.microsoft.com/en-us/cpp/preprocessor/region-endregion ;
		// overrides of virtual functions must go first;
#pragma region __msg_handler_callbacks__
	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnErase   (const HDC _dev_ctx) override final;
		err_code IEvtDraw_OnPaint   (const w_param, const l_param) override final;

	private:  // ILifeEvtSink override(s);
		err_code IEvtLife_OnClose   (const w_param, const l_param) override final; // reminder: if result is __s_ok, this window is still open;
		err_code IEvtLife_OnCreate  (const w_param, const l_param) override final;
		err_code IEvtLife_OnDestroy (const w_param, const l_param) override final;

	private: // ISysEvtSink override(s);
		err_code IEvtSys_OnSysCmd   (const w_param, const l_param) override final; // reminder: if result is __s_ok, this process will be ended up;

	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const SIZE) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, LPRECT) override final;
#pragma endregion
	
	private:
		CWnd& operator = (const CWnd&) = delete;
		CWnd& operator = (CWnd&&) = delete;
	};

}}}

typedef ebo::boo::gui::CWnd TWnd;

#endif/*_WIN_GUI_WND_H_INCLUDED*/