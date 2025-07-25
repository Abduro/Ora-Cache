/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Oct-2021 at 10:26:27.1648335 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window adapter base interface implementation file.
*/
#include "wnd.base.h"

using namespace ex_ui::popup;

/////////////////////////////////////////////////////////////////////////////

CAtom:: CAtom (void) : m_atom(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAtom::~CAtom (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CAtom::Error (void) const { return this->m_error; }

bool  CAtom::Is_valid (void) const { return this->m_atom != 0; }

err_code CAtom::Register (_pc_sz _cls_name, const WNDPROC _p_proc) {
	_cls_name; _p_proc;
	this->m_error << __METHOD__ <<  __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;
#if (1)
	if (nullptr == _cls_name)
		return this->m_error << __e_pointer;
#endif
	CString cls_name(_cls_name); cls_name.Trim();

	if (cls_name.IsEmpty())
		return this->m_error << __e_inv_arg = _T("Input class name is invalid;");

	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));

	WNDCLASSEX wnd_cls = { 0 }; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw ;
	this->m_atom = (ATOM)::GetClassInfoEx(h_instance, (_pc_sz)cls_name, &wnd_cls);
	if (this->m_atom)
		return this->Error(); // already registered the class with such name;

	wnd_cls.cbSize        = sizeof(WNDCLASSEX);
	wnd_cls.style         = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	wnd_cls.lpfnWndProc   = _p_proc ? _p_proc : ::DefWindowProc;
	wnd_cls.hInstance     = h_instance;
	wnd_cls.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject ;
	wnd_cls.lpszClassName = (_pc_sz)cls_name;

	this->m_atom = ::RegisterClassEx(&wnd_cls);
	if (0 == this->m_atom)
		this->m_error.Last();

	this->m_cls_name = cls_name;

	return this->Error();
}

err_code CAtom::Unregister (void) {

	this->m_error << __METHOD__ <<  __s_ok;

	if (false == this->Is_valid())
		return this->Error();  // nothing is to unregister, that's okay;

	if (this->m_cls_name.IsEmpty())
		return this->m_error << __e_not_expect;

	const
	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));

	if (false == ::UnregisterClass((_pc_sz)this->m_cls_name, h_instance))
		return this->m_error.Last();

	this->m_atom = 0;
	this->m_cls_name.Empty();

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////
const
CAtom& CAtom::operator >>(CString& _cls_name) const { _cls_name = this->m_cls_name; return *this; }

CAtom::operator ATOM (void) const { return this->m_atom; }

/////////////////////////////////////////////////////////////////////////////

CWndBase:: CWndBase (_pc_sz _lp_sz_cls_name){
	_lp_sz_cls_name;
	m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	if (false && _lp_sz_cls_name && ::_tcslen(_lp_sz_cls_name)) { // it does not work because on this stage the class info is not initialized;
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

#if (0)
ATL::CWndClassInfo& CWndBase::GetWndClassInfo (void) {
	static ATL::CWndClassInfo wc = {
		0
	};
}
#endif
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

const
CAtom&  CWndBase::Atom  (void) const { return this->m_atom ; }
CAtom&  CWndBase::Atom  (void)       { return this->m_atom ; }
TError& CWndBase::Error (void) const { return this->m_error; }

const
TMsgHandlers& CWndBase::Handlers (void) const { return this->m_handlers; }
TMsgHandlers& CWndBase::Handlers (void)       { return this->m_handlers; }

/////////////////////////////////////////////////////////////////////////////