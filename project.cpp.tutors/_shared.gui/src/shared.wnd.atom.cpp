/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Sep-2025 at 21:53:29.357, UTC+4, Batumi, Tuesday;
	This is Ebo Pack system window atom wrapper interface implementation file;
*/
#include "shared.wnd.atom.h"
#include "shared.wnd.msg.h"
#include "shared.preproc.h"

using namespace ex_ui::popup;

namespace ex_ui { namespace popup { namespace _impl {

	// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-class-styles ;

	class CWnd_cls_out {
	public:
		CWnd_cls_out (const WNDCLASSEX& _cls) : m_cls_ref(_cls) {}
		CWnd_cls_out (void) = delete; CWnd_cls_out (const CWnd_cls_out&) = delete; CWnd_cls_out (CWnd_cls_out&&) = delete; ~CWnd_cls_out (void) = default;

		CString Styles (void) const {

			CString cs_out;

			if (false){}
			if (this->m_cls_ref.style & CS_BYTEALIGNCLIENT) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_BYTEALIGNCLIENT"); }
			if (this->m_cls_ref.style & CS_BYTEALIGNWINDOW) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_BYTEALIGNWINDOW"); }
			if (this->m_cls_ref.style & CS_CLASSDC) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_CLASSDC"); }
			if (this->m_cls_ref.style & CS_DBLCLKS) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_DBLCLKS"); }
			if (this->m_cls_ref.style & CS_DROPSHADOW)  { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_DROPSHADOW"); }
			if (this->m_cls_ref.style & CS_GLOBALCLASS) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_GLOBALCLASS"); }
			if (this->m_cls_ref.style & CS_HREDRAW)  { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_HREDRAW"); }
			if (this->m_cls_ref.style & CS_NOCLOSE)  { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_NOCLOSE"); }
			if (this->m_cls_ref.style & CS_OWNDC)    { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_OWNDC"); }
			if (this->m_cls_ref.style & CS_PARENTDC) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_PARENTDC"); }
			if (this->m_cls_ref.style & CS_SAVEBITS) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_SAVEBITS"); }
			if (this->m_cls_ref.style & CS_VREDRAW)  { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("CS_VREDRAW"); }

			return  cs_out;
		}

	private:
		const
		WNDCLASSEX& m_cls_ref;
	};

}}}
using namespace ex_ui::popup::_impl;

CWndCls:: CWndCls (void) : m_atom(0), m_wnd_cls{0} {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; m_wnd_cls.cbSize = sizeof(WNDCLASSEX); this->Cfg(e_type::e_cfg_over);
}
CWndCls::~CWndCls (void) {}

err_code  CWndCls::Cfg (const e_type _e_cfg) {
	_e_cfg;
	this->m_error <<__METHOD__ << __s_ok;

	HINSTANCE   hInstance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));
	this->Ref().hInstance = hInstance;

	switch (_e_cfg) {
	case e_type::e_cfg_over: {
			this->Ref().style  = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
		} break;
	case e_type::e_cfg_ctrl:
		this->m_error << __e_not_impl; break;
	default:
		this->m_error << __e_inv_arg = _T("Type of cfg is not supported");
	}

#if (0)
	this->Ref().lpfnWndProc = ::DefWindowProc;
#else
	::Get_router().ApplyTo(this->Ref()); // it is *required* for receiving windows messages through the router procedure;
#endif

#if (0)
	/*  https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw ;
		excerpt from above URL:
		When this member is NULL, an application must paint its own background whenever it is requested to paint in its client area...
	*/
	this->Ref().hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject ;
#endif
	this->Ref().hbrBackground = nullptr;

	return this->Error();
}

TError&   CWndCls::Error (void) const { return this->m_error; }

bool  CWndCls::Is_valid (void) const { return this->m_atom != 0; }

bool  CWndCls::Is_exist (_pc_sz _cls_name) const {
	_cls_name;
	this->m_error << __METHOD__ <<  __s_ok;

	CString cls_name(_cls_name); cls_name.Trim();

	if (cls_name.IsEmpty()) {
		this->m_error << __e_inv_arg = _T("Input class name is invalid;"); // the input arg is invalid, so error is turned on;
		return false;
	}

	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));
	WNDCLASSEX wnd_cls = { 0 };
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassinfoexa ;
	return !!::GetClassInfoEx(h_instance, (_pc_sz) cls_name, &wnd_cls);
}

_pc_sz    CWndCls::Name (void) const { return this->m_wnd_cls.lpszClassName; }
bool      CWndCls::Name (_pc_sz _p_name) {
	_p_name;
	CString cs_name(_p_name); cs_name.Trim();

	const bool b_changed = (false == cs_name.IsEmpty() && !!cs_name.CompareNoCase((_pc_sz) this->m_name));
	if (b_changed) {

		if (cs_name.GetLength() > CWndCls::n_cls_name_max)
			cs_name.Left(CWndCls::n_cls_name_max);

		this->m_name = cs_name;
		this->m_wnd_cls.lpszClassName = (_pc_sz) this->m_name;
	}
	return b_changed;
}

#if defined(_DEBUG)
CString   CWndCls::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{}");
	static _pc_sz pc_sz_pat_n = _T("");
	static _pc_sz pc_sz_pat_r = _T("");

	CString cs_out;
	return  cs_out;
}
#endif

err_code  CWndCls::Register (_pc_sz _cls_name) {
	_cls_name;
	this->m_error << __METHOD__ <<  __s_ok;

	if (this->Is_valid()) // the atom has been already created; doesn't matter with such name it was created, but must be unregistered first;
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (this->Is_exist(_cls_name))
		return this->Error(); // no indication of the error this time, but just returns __s_ok;

	if (__failed(this->Name(_cls_name)))
		return this->Error();

	this->m_atom = ::RegisterClassEx(&this->Ref());
	if (0 == this->m_atom)
		this->m_error.Last();

	return this->Error();
}

err_code  CWndCls::Unregister (void) {

	this->m_error << __METHOD__ <<  __s_ok;

	if (false == this->Is_valid())
		return this->Error();  // nothing is to unregister, that's okay;

	if (this->m_name.IsEmpty())
		return this->m_error << __e_not_expect;

	const
	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));

	if (false == ::UnregisterClass((_pc_sz) this->m_name, h_instance))
		return this->m_error.Last();

	this->m_atom = 0;
	this->m_name.Empty();

	return this->Error();
}

const
WNDCLASSEX&  CWndCls::Ref (void) const { return this->m_wnd_cls; }
WNDCLASSEX&  CWndCls::Ref (void)       { return this->m_wnd_cls; }

uint32_t  CWndCls::Style (void) const    { return this->Ref().style; }    
bool      CWndCls::Style (const uint32_t _u_flags) {
	_u_flags;
	const bool b_changed = this->Style() != _u_flags;
	if (true == b_changed)
		this->Ref().style = _u_flags;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////
const
CWndCls& CWndCls::operator >>(CString& _cls_name) const { _cls_name = this->Name(); return *this; }

CWndCls::operator ATOM (void) const { return this->m_atom; }

const
WNDCLASSEX&  CWndCls::operator ()(void) const { return this->Ref(); }
WNDCLASSEX&  CWndCls::operator ()(void)       { return this->Ref(); }

/////////////////////////////////////////////////////////////////////////////

CCon_cls:: CCon_cls (void) : TBase() { TBase::m_error >>__CLASS__; }
CCon_cls::~CCon_cls (void) {}

err_code   CCon_cls::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	TBase::Name(_T("ConsoleWindowClass"));

	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr)); h_instance;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassinfoexa ;
	if (0 == ::GetClassInfoEx(0, this->Name(), &this->m_wnd_cls))
		TBase::m_error.Last();

	return this->Error();
}