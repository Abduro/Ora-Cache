/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jul-2025 at 10:51:48.442, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI image cache unit test interface declaration file;
*/
#include "ebo_test_$d$.img.cache.h"
#include "ebo_test_$d$.img.stream.h"

#include "uix.theme.named.h"
#include "uix.theme.reg.h"

using namespace ebo::boo::test::cache;

using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace cache { namespace _impl {}}}}}
using namespace ebo::boo::test::cache::_impl;
/////////////////////////////////////////////////////////////////////////////

CCacheList:: CCacheList (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CCacheList::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_list.Print(e_print::e_all));
	_out()();
}

void CCacheList::Create (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_list.Print(e_print::e_all));

	const t_size size{16,16};
	const uint16_t n_count = 2;
	const uint16_t n_delta = 2;

	_out() += TStringEx().Format (
		_T("Input args:%ssize=[w:%u|h:%u](px)%scount=%d%sdelta=%d"), _p_new_line, size.cx, size.cy, _p_new_line, n_count, _p_new_line, n_delta
	);

	if (__failed(this->m_list.Create(size, n_count, n_delta)))
		_out() += this->m_list.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after* : %s"), (_pc_sz) this->m_list.Print(e_print::e_all));

	_out()();
}