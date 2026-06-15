/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 11:49:07.788, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL viewport cache wrapper interface implementation file;
*/
#include "view.port.h"

using namespace ::open_gl::views;

namespace shared { namespace drawable { namespace _impl_d {

static CViewPort g_not_valid;

static _pc_sz p_err_no_active = _T("#__e_state: no active viewport");
static _pc_sz p_err_no_surface = _T("#__e_hwnd: surface window handle is not valid");
static _pc_sz p_err_no_cached = _T("#__e_not_found: given surface has no cache");

	class CHelper {
	public:
		CHelper (void) = default; CHelper (const CHelper&) = delete; CHelper (CHelper&&) = delete; ~CHelper (void) = default;

		static err_code Is_valid (const HWND _h_surface, CError& _error) {
			_h_surface; _error;
			if (nullptr == _h_surface || false == !!::IsWindow(_h_surface))
				_error <<__e_hwnd = p_err_no_surface;
			return _error;
		}

	private:
		CHelper& operator = (const CHelper&) = delete; CHelper& operator = (CHelper&&) = delete;
	};
}}} using namespace shared::drawable::_impl_d;

#pragma region cls::CViewports{}

CViewports::CViewports (void) : m_active(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CViewports::Activate (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(_h_surface, this->m_error)))
		return this->Error();

	if (this->m_cached.empty())
		return this->m_error << (err_code)TErrCodes::eData::eEmpty = _T("__e_empty: viewport cache is empty");

	view_cache_t::const_iterator it_found = this->m_cached.find(_h_surface);
	if (it_found == this->m_cached.end())
		return this->m_error << (err_code)TErrCodes::eData::eNotFound = p_err_no_cached;

	this->m_active = _h_surface;

	return this->Error();
}

const
CViewPort& CViewports::Active (void) const {

	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_active == nullptr) {
	    this->m_error << (err_code)TErrCodes::eExecute::eState = p_err_no_active; return g_not_valid;
	}

	view_cache_t::const_iterator it_found = this->m_cached.find(this->m_active);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}
CViewPort& CViewports::Active (void) {

	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_active == nullptr) {
	    this->m_error << (err_code)TErrCodes::eExecute::eState =p_err_no_active; return g_not_valid;
	}

	view_cache_t::iterator it_found = this->m_cached.find(this->m_active);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}

err_code CViewports::Add (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(_h_surface, this->m_error)))
		return this->Error();

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

TError&  CViewports::Error (void) const { return this->m_error; }

const
CViewPort& CViewports::Get (const HWND _h_surface) const {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(_h_surface, this->m_error))) {
		return g_not_valid;
	}

	view_cache_t::const_iterator it_found = this->m_cached.find(_h_surface);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}
CViewPort& CViewports::Get (const HWND _h_surface){
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(_h_surface, this->m_error))) {
		return g_not_valid;
	}

	view_cache_t::iterator it_found = this->m_cached.find(_h_surface);

	if (it_found == this->m_cached.end())
	     return g_not_valid;
	else return it_found->second;
}

err_code CViewports::Remove (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(_h_surface, this->m_error))) {
		return this->Error();
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