#ifndef _DIRECT_X_WRAP_H_INCLUDED
#define _DIRECT_X_WRAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2025 at 02:50:32.714, UTC+4, Batumi, Tuesday;
	This is Ebo Pack DirectX draw render connect wrapper interface declaration file;
*/
#include "win.gui_module.h"
#include "handlers.h"
#include "color.rgb.h"
#include "direct_x.device.1.h"
#include "direct_x.target.h"
#include "direct_x.texture.h"

namespace ebo { namespace boo { namespace gui { namespace render {

	using namespace ebo::boo::gui;
	using namespace ex_ui::message::handlers;
	using namespace ex_ui::draw::direct_x::_11; // not good approach because there is _12 namespace too; and some classes have the same names;

//	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using CTarget  = ex_ui::draw::direct_x::_11::CTarget;
	using CTexture = ex_ui::draw::direct_x::_11::_2D::CTexture;

	class CRender_Wrap : public IFormEvtSink/*, IDrawEvtSink*/ {
	public:
		 CRender_Wrap (void) ; CRender_Wrap (const CRender_Wrap&) = delete; CRender_Wrap (CRender_Wrap&&) = delete;
		~CRender_Wrap (void) ;

	public:
		TError&  Error (void) const;
		err_code Init  (const HWND _h_target); // sets the target window handle for creating target view object;
		err_code Term  (void);                 // this method and above one are called by main window on 'create' and 'destroy' events;

		CTarget& Target(void);

//	private:  // IDrawEvtSink override(s);
//		err_code IEvtDraw_OnErase (const HDC _dev_ctx) override final;

	private: // IFormEvtSink override(s); 
		err_code IEvtFrame_OnSize   (const IFormEvtSink::eState, const SIZE) override final;
		err_code IEvtFrame_OnSizing (const IFormEvtSink::eEdges, LPRECT) override final;

	private:
		CError   m_error ;
		CDevice  m_device;
		CTarget  m_target;

	private:
		CRender_Wrap&  operator = (const CRender_Wrap&) = delete;
		CRender_Wrap&  operator = (CRender_Wrap&&) = delete;
	};

}}}}
typedef ebo::boo::gui::render::CRender_Wrap TRender;

TRender& _render(void);

#endif/*_DIRECT_X_WRAP_H_INCLUDED*/