#ifndef _DIRECT_X_SURFACE_H_INCLUDED
#define _DIRECT_X_SURFACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04=May-2025 at 19:58:52.0505, UTC+4, Batumi, Sunday;
	This is Ebo Pack DirectX draw render surface window interface declaration file;
*/
#include "win.gui.inc.h"
#include "handlers.h"
#include "wnd.base.h"
#include "ebo.sha.gui.theme.h"
#include "direct_x.wrap.h"      // ToDo:: if it is placed to header 'win.gui_wnd.h', the compilation is failed;

namespace ebo { namespace boo { namespace gui { namespace render {

	using namespace ebo::boo::gui;
	using namespace ex_ui::message::handlers;

	using ex_ui::popup::CWndBase;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;

	class CSurface : public CWndBase, IDrawEvtSink, IFormEvtSink { typedef CWndBase TBase;
	public:
		 CSurface (void) ; CSurface (const CSurface&) = delete; CSurface (CSurface&&) = delete;
		~CSurface (void) ;

	err_code  Create (const HWND _h_parent, const t_rect& _rc_place);

	private:  // IDrawEvtSink override(s);
		err_code IEvtDraw_OnPaint   (const w_param, const l_param) override final;

	public: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnMove   (const t_point& _top_left_client_area) override final;
		err_code IEvtFrame_OnMoving (const t_rect* _p_wnd_coords) override final;
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const SIZE) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, LPRECT) override final;

	private:
		CSurface& operator = (const CSurface&) = delete;
		CSurface& operator = (CSurface&&) = delete;
	};

}}}}

#endif/*_DIRECT_X_SURFACE_H_INCLUDED*/