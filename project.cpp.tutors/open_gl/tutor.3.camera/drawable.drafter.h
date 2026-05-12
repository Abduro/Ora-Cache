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

namespace shared { namespace drawable {

	using CCamera = ::open_gl::CCamera;
	using CModel = ex_ui::draw::open_gl::models::CBase;
	using CView = ex_ui::draw::open_gl::views::CBase;

	using IMouse_Handler = ex_ui::popup::messages::IMouse_Handler;
	using CEvent = ex_ui::popup::messages::IMouse_Handler::CEvent;

	using c_scaled = ex_ui::draw::open_gl::math::c_scaled_4x4;
	using c_mutex = ::std::recursive_mutex;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glscalef ;
	// thread safe;
	class CScale {
	public:
		CScale (void); CScale (const CScale&) = delete; CScale (CScale&&) = delete; ~CScale (void) = default;

		bool Is_changed (void) const;
		void Is_changed (const bool);

		float Get (void) const;              // gets the factor value;
		void  Set (const int32_t _n_factor); // sets the factor value;

		c_scaled operator ()(void) const;    // gets a copy of scaled matrix;

	private:
		CScale& operator = (const CScale&) = delete; CScale& operator = (CScale&&) = delete;
		bool     m_changed;
		float    m_factor;
		c_scaled m_scaled;
	};

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
		err_code  IMouse_OnEvent (const CEvent&) override final;
		err_code  IMouse_OnWheel (const CEvent&, const int32_t _delta) override final; // if it occurs, it will come before IMouse_OnEvent();

	protected:
		virtual void Run (void) override final;

	private:
		CDrafter& operator = (const CDrafter&) = delete; CDrafter& operator = (CDrafter&&) = delete;
		CModel    m_model;
		CView     m_view;
		HWND      m_surface;
		t_point   m_mouse;   // this is the last position of the mouse cursor at the moment of mouse message handling;
		CCamera   m_camera;
		CScale    m_scale;
	};
}}

#endif/*_DRAWABLE_DRAFTER_H_INCLUDEDE*/