/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Oct-2026 at 10:19:04.006, UTC+4, Batumi, Tuesday;
	This is virtual camera FoV test view interface declaration file.
*/
#include "test.1.view.h"

using namespace ::test::gui::views::_1;

#pragma region cls::CView{}

CView:: CView (void) { TBase::m_error >> TString().Format(_T("test.1.fov.%s"), (_pc_sz)__CLASS__); }
CView::~CView (void) {}

err_code CView::Create (const HWND hParent, const rect_t& rect) {
	hParent; rect;
	if (__failed(TBase::Create(hParent, rect)))
		return this->m_error = TBase::Error();

	return TBase::Error();
}

err_code CView::Destroy (void) {
	return TBase::Destroy();
}

#pragma endregion