/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:51:59.009,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control layout interface implementation file;
*/
#include "sfx.trkball.lay.h"
#include "sfx.trkball.ctrl.h"

using namespace ex_ui::controls::sfx::track;
using namespace ex_ui::controls::sfx::track::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#endif

#ifndef __W
#define __W(rc) (rc.right - rc.left)
#endif

namespace ex_ui { namespace controls { namespace sfx { namespace track { namespace _impl {

	const t_size& Get_req_size (void) {
		static t_size req_size {64, 64};
		return req_size;
	}

}}}}}
using namespace ex_ui::controls::sfx::track::_impl;

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_padding(5,5,-5,-5), m_pref_sz{64,64} { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

TError&   CLayout::Error   (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding (void) const { return this->m_padding; }
CPadding& CLayout::Padding (void)       { return this->m_padding; }

const
t_size&   CLayout::Pref_Sz (void) const { return this->m_pref_sz; }
err_code  CLayout::Pref_Sz (const t_size& _pref_sz) {
	_pref_sz;
	m_error << __METHOD__ << __s_ok;

	if (_pref_sz.cx < Get_req_size().cx || _pref_sz.cy < Get_req_size().cy)
		return this->m_error << __e_inv_arg = TString().Format(_T("The min.size is req: w=%u;h=%u"), Get_req_size().cx, Get_req_size().cy);
	if (_pref_sz.cx != _pref_sz.cy)
		return this->m_error << __e_inv_arg = _T("The size must be a square");

	this->m_pref_sz = _pref_sz;

	return this->Error();
}