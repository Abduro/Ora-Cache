/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:41:07.778, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface implementation file;
*/
#include "shared.wnd.base.h"

using namespace ex_ui::popup;

CAtom:: CAtom (void) : m_atom(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAtom::~CAtom (void) {}

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
	wnd_cls.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
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