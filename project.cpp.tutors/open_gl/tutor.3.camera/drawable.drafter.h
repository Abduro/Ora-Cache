#ifndef _DRAWABLE_DRAFTER_H_INCLUDEDE
#define _DRAWABLE_DRAFTER_H_INCLUDEDE
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:02:41.310, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface declaration file;
*/
#include "drawable.defs.h"
#include "runner.tpl.h"

#include "model.base.h"
#include "view.base.h"

namespace shared { namespace drawable {

	using CTplRunner = shared::runnable::threads::pool::CTplRunner;
	using CModel = ex_ui::draw::open_gl::models::CBase;
	using CView = ex_ui::draw::open_gl::views::CBase;

	class CDrafter : public CTplRunner { typedef CTplRunner TBase;
	public:
		CDrafter (void); CDrafter (const CDrafter&) = delete; CDrafter (CDrafter&&) = delete; ~CDrafter (void);

		err_code OnCreate (const HWND _h_surface);
		err_code OnDestroy (void);

		const
		CModel&  Model (void) const;
		CModel&  Model (void) ;
		const
		CView&   View (void) const;
		CView&   View (void) ;

	protected:
		virtual void Run (void) override final;

	private:
		CDrafter& operator = (const CDrafter&) = delete; CDrafter& operator = (CDrafter&&) = delete;
		CModel  m_model;
		CView   m_view;
	};
}}

#endif/*_DRAWABLE_DRAFTER_H_INCLUDEDE*/