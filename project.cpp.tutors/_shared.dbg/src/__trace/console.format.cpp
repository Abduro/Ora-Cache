/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 11:30:54.452, UTC+4, Batumi, Saturday;
	This is system console format interface implementation file;
*/
#include "console.format.h"
#include "shared.preproc.h"

using namespace shared::console;

namespace shared { namespace console  { namespace _impl {

}}} using namespace shared::console::_impl;

#pragma region cls::CBkgnd{}
/* regardless the class fields are initialized by zero,
   the error state indicates the class is still not initialized, i.e. neither Color() nor Index() is called yet;
*/
CBkgnd:: CBkgnd (void) : m_clr_ref(0), m_clr_ndx(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }
CBkgnd::~CBkgnd (void) {}

TError&  CBkgnd::Error (void) const { return this->m_error; }

colorref CBkgnd::Color (void) const { return this->m_clr_ref; }

err_code CBkgnd::Color (const colorref _clr) {
	_clr;
	this->m_error <<__METHOD__<<__s_ok;

	CScreenBufferEx buffer_ex;
	
	if (__failed(buffer_ex.Get()))
		return this->m_error = buffer_ex.Error();

	TScrBufInfoEx&  info_set = buffer_ex.Ref();
	info_set.ColorTable[0] = _clr;

	if (__failed(buffer_ex.Set()))
		this->m_error = buffer_ex.Error();
	else
		this->m_clr_ref;

	return this->Error();
}

#pragma endregion
#pragma region cls::CFormat{}

#pragma endregion