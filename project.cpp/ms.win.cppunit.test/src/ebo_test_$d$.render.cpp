/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:41:06.363, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.render.h"

using namespace ebo::boo::test::draw;

/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (const bool _b_verb) : m_b_verb(_b_verb){
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	this->m_buffer << (IBufferSink* const)&this->m_sync;
}

/////////////////////////////////////////////////////////////////////////////

void CBuffer::Set (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += TStringEx().Format(_T("swap desc value sync before: count=%d;usage=%d"),
		this->m_buffer.Count(), this->m_buffer.Usage()
	);

	this->m_buffer.Set(3, TUsage::e_read);

	_out() += this->m_buffer.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("swap desc value sync after: count=%d;usage=%d"),
		this->m_buffer.Count(), this->m_buffer.Usage()
	);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CEffect:: CEffect (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	this->m_effect << (uint32_t* const)&this->m_sync;
}

/////////////////////////////////////////////////////////////////////////////

void CEffect::Set (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += TStringEx().Format(_T("effect value sync before: %d"), this->m_sync);

	this->m_effect.Set(TEffect::e_value::e_flp_seq);

	_out() += this->m_effect.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("effect value sync after: %d"), this->m_sync);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CSample:: CSample (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	this->m_sample << (ISample_Sync* const)&this->m_sync;
}

/////////////////////////////////////////////////////////////////////////////

void CSample::Set (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += TStringEx().Format(_T("sample sync values before: count=%d;quality=%d"),
		this->m_sample.Count(), this->m_sample.Quality()
	);

	this->m_sample.Set(1, 2);

	_out() += this->m_sample.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("sample sync values after: count=%d;quality=%d"),
		this->m_sample.Count(), this->m_sample.Quality()
	);
	_out()();
}