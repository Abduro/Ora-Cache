/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 12:30:57.965, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object common definition file;
*/
#include "drawable.defs.h"

using namespace shared::drawable;

namespace shared { namespace drawable { namespace _impl_d { void __warning_lnk_4221 (void) {} }}}

using namespace ::open_gl::views;
using CCache =  ::open_gl::views::CCache;

#pragma region cls::CCache{}

static CViewPort g_not_valid;

static _pc_sz p_err_no_active = _T("#__e_state: no active viewport");
static _pc_sz p_err_iv_surface = _T("#__e_inv_arg: surface window handle is not valid");
static _pc_sz p_err_no_cached = _T("__e_not_found: given surface has no cache");

CCache::CCache (void) : m_active(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCache::Activate (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_surface)
		return this->m_error <<__e_hwnd = _T("#__e_hwnd: invalid surface handle");

	if (this->m_cached.empty())
		return this->m_error << (err_code)TErrCodes::eData::eEmpty = _T("__e_empty: viewport cache is empty");

	view_cache_t::const_iterator it_found = this->m_cached.find(_h_surface);
	if (it_found == this->m_cached.end())
		return this->m_error << (err_code)TErrCodes::eData::eNotFound = p_err_no_cached;

	this->m_active = _h_surface;

	return this->Error();
}

const
CViewPort& CCache::Active (void) const {

	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_active == nullptr) {
	    this->m_error << (err_code)TErrCodes::eExecute::eState = p_err_no_active; return g_not_valid;
	}

	view_cache_t::const_iterator it_found = this->m_cached.find(this->m_active);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}
CViewPort& CCache::Active (void) {

	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_active == nullptr) {
	    this->m_error << (err_code)TErrCodes::eExecute::eState =p_err_no_active; return g_not_valid;
	}

	view_cache_t::iterator it_found = this->m_cached.find(this->m_active);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}

err_code CCache::Add (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_surface || false == !!::IsWindow(_h_surface))
		return this->m_error <<__e_hwnd = p_err_iv_surface;

	view_cache_t::iterator it_found = this->m_cached.find(_h_surface);

	if (it_found != this->m_cached.end()) { // if given surface already has associated viewport, just makes it active and silently returns __s_ok;
		this->m_active = _h_surface;
		return this->Error();
	}

	t_rect rc_client = {0};
	if (false == !!GetClientRect(_h_surface, &rc_client))
		return this->m_error.Last();

	CViewPort v_port; v_port << rc_client; // if an error occurs during setting the client rectangle to the viewport, it does not prevent from adding to cache;

	try {
		this->m_cached.insert(::std::make_pair(_h_surface, v_port));
		this->m_active = _h_surface;
	} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }

	__trace_impt_2(_T("The viewport of '_h_surface' %s is cached;\n"), TString()._addr_of(_h_surface, _T("0x%08x")));

	return this->Error();
}

TError&  CCache::Error (void) const { return this->m_error; }

const
CViewPort& CCache::Get (const HWND _h_surface) const {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_surface || false == !!::IsWindow(_h_surface)) {
		this->m_error <<__e_hwnd = p_err_iv_surface;
		return g_not_valid;
	}

	view_cache_t::const_iterator it_found = this->m_cached.find(_h_surface);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}
CViewPort& CCache::Get (const HWND _h_surface){
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_surface || false == !!::IsWindow(_h_surface)) {
		this->m_error <<__e_hwnd = p_err_iv_surface;
		return g_not_valid;
	}

	view_cache_t::iterator it_found = this->m_cached.find(_h_surface);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}

err_code CCache::Remove (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_surface || false == !!::IsWindow(_h_surface)) {
		return this->m_error <<__e_hwnd = p_err_iv_surface;
	}

	view_cache_t::iterator it_found = this->m_cached.find(_h_surface);

	if (it_found == this->m_cached.end())
		this->m_error << (err_code)TErrCodes::eData::eNotFound = p_err_no_cached;
	else {
		this->m_cached.erase(it_found);
		__trace_impt_2(_T("The viewport of '_h_surface' %s is removed from cache;\n"), TString()._addr_of(_h_surface, _T("0x%08x")));
	}
	return this->Error();
}

#pragma endregion;

TViewPortCache& ::Get_ViewPorts (void) {
	static TViewPortCache cache;
	return cache;
}

#pragma region cls::c_view_matrix{}

c_view_matrix::c_view_matrix (void) : base_t() {}
	/* cols:  #0   #1   #2   #3    entry/cell is of interest;
	rows: #0 1.0  0.0  0.0  X.X << for along x-axis shift;
	      #1 0.0  1.0  0.0  Y.Y << for along y-axis shift;
	      #2 0.0  0.0  1.0  Z.Z << for along z-axis shift; 
	      #3 0.0  0.0  0.0  1.0
	*/
float&  c_view_matrix::Shift_X (const int32_t _delta_x) {
	return ((*this)().Cell(3, 0) += ::Get_ViewPorts().Active().Get_X(_delta_x));
}

float&  c_view_matrix::Shift_Y (const int32_t _delta_y) {
	return ((*this)().Cell(3, 1) += ::Get_ViewPorts().Active().Get_Y(_delta_y));
}

float&  c_view_matrix::Shift_Z (const int32_t _wheel_value) {
	return ((*this)().Cell(3, 2) += float(_wheel_value));
}

const
c_mat4x4& c_view_matrix::operator ()(void) const { return (base_t&)*this; }
c_mat4x4& c_view_matrix::operator ()(void)       { return (base_t&)*this; }

#pragma endregion