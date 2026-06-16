#ifndef _DRAWABLE_DRAFTER_H_INCLUDEDE
#define _DRAWABLE_DRAFTER_H_INCLUDEDE
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:02:41.310, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface declaration file;
*/
#include "drawable.defs.h"
#include "shared.wnd.msg.h"

#include "camera.base.h"
#include "model.base.h"
#include "view.base.h"
#include "view.port.h"
#include "shapes\shape.tria.h"

namespace shared { namespace drawable { using namespace ::shared::defs;

	using CCamera = ::open_gl::CCamera;
	using CModel = ::open_gl::models::CBase;
	using CView = ::open_gl::views::CBase;

	using IMouse_Handler = ex_ui::popup::messages::IMouse_Handler;
	using CEvent = ex_ui::popup::messages::IMouse_Handler::CEvent;

	using c_mutex = ::std::recursive_mutex;

	using CTria = ::open_gl::shapes::CTria;

	class CDrafter : public CTplRunner, public IMouse_Handler { typedef CTplRunner TBase;
	public:
		CDrafter (void); CDrafter (const CDrafter&) = delete; CDrafter (CDrafter&&) = delete; ~CDrafter (void);
		const
		CCamera&  Camera (void) const;
		CCamera&  Camera (void) ;

		err_code  OnCreate (const HWND _h_surface);
		err_code  OnDestroy (void);

		const
		CModel&   Model (void) const;
		CModel&   Model (void) ;
		const
		CView&    View (void) const;
		CView&    View (void) ;

		TError&   IMouse_Error (void) const override final;
		err_code  IMouse_OnButton (const CEvent&) override final;
		err_code  IMouse_OnMove  (const CEvent&) override final;
		err_code  IMouse_OnWheel (const CEvent&, const int32_t _delta) override final; // if it occurs, it will come before IMouse_OnButton();

	protected:
		virtual void Run (void) override final;

	private:
		CDrafter& operator = (const CDrafter&) = delete; CDrafter& operator = (CDrafter&&) = delete;
		CModel    m_model;
		CView     m_view;
		HWND      m_surface;
		CCamera   m_camera;
		CTria     m_tria;
	};
}}

#endif/*_DRAWABLE_DRAFTER_H_INCLUDEDE*/