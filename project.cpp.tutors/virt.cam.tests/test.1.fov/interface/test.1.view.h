#ifndef _TEST_1_VIEW_H_INCLUDED
#define _TEST_1_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Oct-2026 at 10:17:55.873, UTC+4, Batumi, Tuesday;
	This is virtual camera FoV test view interface declaration file.
*/
#include "common.view.h"

namespace test { namespace gui { namespace views { namespace _1 { using namespace test::gui::views;

	using CBase = ::test::gui::views::CBase;

	class CView : public CBase { typedef CBase TBase;
	public:
		 CView (void); CView (const CView&) = delete; CView (CView&&) = delete;
		~CView (void);

		err_code Create (const HWND hParent, const rect_t& rect);
		err_code Destroy (void);

	private:
		CView& operator = (const CView&) = delete; CView& operator = (CView&&) = delete;
	};

}}}}

#endif/*_TEST_1_VIEW_H_INCLUDED*/