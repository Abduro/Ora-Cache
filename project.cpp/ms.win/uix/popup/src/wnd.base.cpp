/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Oct-2021 at 10:26:27.1648335 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window adapter base interface implementation file.
*/
#include "wnd.base.h"

using namespace ex_ui::popup;


/////////////////////////////////////////////////////////////////////////////

CWndBase:: CWndBase (_pc_sz _lp_sz_cls_name){
	_lp_sz_cls_name;
	m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	if (_lp_sz_cls_name && ::_tcslen(_lp_sz_cls_name)) {
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw;
		static const UINT sz_req_of_cls_name = 256;

		ATL::CWndClassInfo& cls_info = TWindow::GetWndClassInfo();

		LPTCH lp_sz_cls_name = const_cast<LPTCH>(cls_info.m_wc.lpszClassName);

		if (lp_sz_cls_name && ::_tcslen (lp_sz_cls_name)) {
			::RtlZeroMemory(lp_sz_cls_name, sizeof(TCHAR) * ::_tcslen (lp_sz_cls_name));
		}

		errno_t e_result = ::_tcsncpy_s(lp_sz_cls_name, sz_req_of_cls_name, _lp_sz_cls_name, ::_tcslen(_lp_sz_cls_name));
		if (__s_ok != e_result)
			(m_error << __e_no_memory) = _T("Class name set is failed;");
	}
}

CWndBase::~CWndBase (void) {}

/////////////////////////////////////////////////////////////////////////////
#if (0)
/////////////////////////////////////////////////////////////////////////////
const
CBrush&   CWndBase::BkgBrush (void) const {

	const bool b_valid = NULL != m_bkg_brush.m_hBrush;

	if (false == b_valid) {

		TBase::m_error << __METHOD__ << S_OK;

		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclasslongptra
		ULONG_PTR ptr_brush = ::GetClassLongPtr(*this, GCLP_HBRBACKGROUND);
		if (NULL == ptr_brush) {
			TBase::m_error << __LastErrToHresult();
		}
		else {
			HBRUSH hBrush = (HBRUSH)ptr_brush;
			// https://stackoverflow.com/questions/55229307/how-to-create-a-pen-that-is-the-same-color-as-that-of-a-solid-brush
			LOGBRUSH log_brush = {0};
			// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobject
			if (!::GetObject(hBrush, sizeof(LOGBRUSH), &log_brush)) {
				TBase::m_error << __LastErrToHresult();
			}
			else {
				this->m_bkg_brush.CreateSolidBrush(log_brush.lbColor);
				if (NULL == m_bkg_brush.m_hBrush) // still be sucking dick;
					TBase::m_error << E_UNEXPECTED;
			}
		}
	}
	return this->m_bkg_brush;
}

err_code   CWndBase::BkgBrush (COLORREF _clr_bkg) {
	_clr_bkg;
	TBase::m_error << __METHOD__ << S_OK;

	if (__clr_none == _clr_bkg)
		return (TBase::m_error << E_INVALIDARG);

	if (false == !!TWindow::IsWindow())
		return (TBase::m_error << OLE_E_BLANK);

	if (false == m_bkg_brush.IsNull())
		m_bkg_brush.DeleteObject();

	m_bkg_brush.CreateSolidBrush(_clr_bkg);
	if (true == m_bkg_brush.IsNull())
		return (TBase::m_error << E_OUTOFMEMORY);

	if (0 == ::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)this->m_bkg_brush.m_hBrush))
		TBase::m_error << __LastErrToHresult();

	return TBase::m_error;
}
#endif

TErrorRef CWndBase::Error (void) const { return this->m_error; }

const
TMsgHandlers& CWndBase::Handlers (void) const { return this->m_handlers; }
TMsgHandlers& CWndBase::Handlers (void)       { return this->m_handlers; }

/////////////////////////////////////////////////////////////////////////////