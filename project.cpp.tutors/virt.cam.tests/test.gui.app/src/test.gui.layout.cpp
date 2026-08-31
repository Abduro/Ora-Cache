/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:26:30.688, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window layout interface implementation file;
*/
#include "test.gui.layout.h"
#include "test.gui.view.h"

#define _what __METHOD__
using namespace ::test::app;

namespace test { namespace app { namespace _impl {

	class CLayout_Default {
	public:
		class CPane {
		public:
			 CPane (void) {} CPane (const CPane&) = delete; CPane (CPane&&) = delete;
			~CPane (void) {}
		public:
			uint32_t Height (void) const { return 35; } // this is the default height of the status bar control;
		private:
			CPane& operator = (const CPane&) = delete;
			CPane& operator = (CPane&&) = delete;
		};
		 CLayout_Default (void) { this->m_padding.Set(10,10,-10,-10); } // sets nagative values to the right and the bottom gaps!
		 CLayout_Default (const CLayout_Default&) = delete; CLayout_Default (CLayout_Default&&) = delete;
		~CLayout_Default (void) {}

		const
		CPadding& Padding(void) const { return this->m_padding; } // this is the padding that is applied to the main window client area;
		const
		CPane&  Pane (void) const { return this->m_pane; }

	private:
		CLayout_Default& operator = (const CLayout_Default&) = delete;
		CLayout_Default& operator = (CLayout_Default&&) = delete;

		CPadding m_padding;
		CPane    m_pane;
	};

}}} using namespace ::test::app::_impl;

#pragma region cls::CLayout{}

CLayout::CLayout (void) : m_draw_area{0}{ this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
const
rect_t&  CLayout::DrawArea (void) {
	this->m_error << __METHOD__ << __s_ok;
	this->Update();
	return this->m_draw_area;
}

TError&  CLayout::Error  (void) const { return this->m_error; }
bool     CLayout::Is_valid (void) const { return !!this->Window().IsWindow(); }
const
CPadding&CLayout::Padding (void) const { return this->m_padding; }
CPadding&CLayout::Padding (void)       { return this->m_padding; }

err_code CLayout::Update (void) {
	
	if (false == !!this->Window().IsWindow()) {
		return this->m_error << _what << __e_hwnd;
	}

	rect_t rect_ = {0};
	if (false == !!this->Window().GetClientRect(&rect_)) {
		return (this->m_error << _what).Last();
	}

	return this->Update(rect_);
}

err_code CLayout::Update (const rect_t& _rect) {
	_rect;
	if (::IsRectEmpty(&_rect)) {
		return this->m_error << _what << __e_rect;
	}
	this->m_draw_area = _rect; // assigns the draw area rectangle to the input one;  

#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	CLayout_Default().Padding().ApplyTo(this->m_draw_area); // applies padding to the draw area rectangle;
	::shared::Get_View().Pages().Get().Layout().Update(this->m_draw_area);
#endif
#if defined(_test_case_lvl) && (_test_case_lvl != 0)

	this->m_draw_area.bottom -= CLayout_Default().Pane().Height(); // updates the bottom value for reserving the space of pane control;

	rect_t rect_pane = _rect;
	rect_pane.top = rect_pane.bottom - CLayout_Default().Pane().Height();
	/*
		the issue which appears here is this layout works in client area coordinates of the main window,
		but the view components, including this test pane object, use the in-memory device context which draws only in particular area,
		and finally, the clipping being made for better performance gives not proper result due to the components resides outside of
		the draw area of the in-memory device context; for solving this issue the following may be made:
		(a) to re-calculate component points inside of their draw function;
		(b) each component of the view must be windowed for better isolation from each one other; (the better solution than above one);
	*/
	shared::Get_View().Pane().Layout().Update(rect_pane);
#endif
	return __s_ok;
}

const
CWindow& CLayout::Window (void) const { return this->m_wnd; }
CWindow& CLayout::Window (void)       { return this->m_wnd; }

CLayout& CLayout::operator <<(const HWND _h_app_wnd) { this->m_wnd = _h_app_wnd;  return *this; }

#pragma endregion

namespace shared {
	TLayout&  Get_Layout (void) {
		static
		TLayout cs_layout;
		return  cs_layout;
	}
}