/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-Apr-2024 at 08:24:31.4391778, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack UIX libs unit test logger interface implementation file.
*/
#include "_log.h"

using namespace ebo::boo::test;

namespace ebo { namespace boo { namespace test { namespace _impl {

	class CIndent {
	public:
		CIndent (const CIndent&) = delete; CIndent (CIndent&&) = delete; ~CIndent (void) = default;
		CIndent (void) : m_value(1) {
			this->m_indent.Format(_T("%*c"), this->m_value, _T('\t'));
		}

		void operator ++(int) { this->m_value += 1; this->m_indent.Format(_T("%*c"), this->m_value, _T('\t')); }
		void operator --(int) { if (this->m_value > 0) m_value -= 1; this->m_indent.Format(_T("%*c"), this->m_value, _T('\t')); }

		CIndent& operator += (const uint32_t _u_steps) {
			this->m_value += _u_steps; this->m_indent.Empty();
			for (uint32_t i_ = 0; i_ < this->m_value; i_++)
				this->m_indent +=  _T("\t");
			return *this;
		}
		CIndent& operator -= (const uint32_t _u_steps) {
			if (this->m_value >= _u_steps)
				this->m_value -= _u_steps;
			this->m_indent.Empty();
			for (uint32_t i_ = 0; i_ < this->m_value; i_++)
				this->m_indent +=  _T("\t");
			return *this;
		}

		operator _pc_sz (void) const { return (_pc_sz) this->m_indent; }

	private:
		CIndent& operator = (const CIndent&) = delete; CIndent& operator = (CIndent&&) = delete;
		uint32_t m_value ;
		CString  m_indent;
	};

	CIndent& _get_indent (void) {
		static CIndent indent; return indent;
	}

}}}}
using namespace _impl;

#pragma region cls::CCache{}

CCache:: CCache (void) : m_prefix(_T("\t")), m_suffix(_T("\n")), m_locked(false) {}
CCache::~CCache (void) {}

void CCache::Clear(void) { this->m_strings.clear(); }

const
TCached& CCache::Get (void) const { return this->m_strings; }
TCached& CCache::Get (void)       { return this->m_strings; }
const
bool&    CCache::Locked (void) const { return this->m_locked; }
bool&    CCache::Locked (void)       { return this->m_locked; }

_pc_sz   CCache::Prefix (void) const   { return this->m_prefix.GetString(); }
void     CCache::Prefix (_pc_sz _prfx) { this->m_prefix = _prfx; }
_pc_sz   CCache::Suffix (void) const   { return this->m_suffix.GetString(); }
void     CCache::Suffix (_pc_sz _sufx) { this->m_suffix = _sufx; }

void     CCache::Output (void) const {

	if (this->m_strings.empty())
		return ;

	CString cs_out;
	const bool b_prefix = !this->m_prefix.IsEmpty();
	const bool b_suffix = !this->m_suffix.IsEmpty(); if (b_suffix) cs_out += this->Suffix(); // for starting new line;

	CString cs_fmt;

	for (size_t i_ = 0; i_ < this->m_strings.size(); i_++) {
		const CString& cs_str = this->m_strings.at(i_);

	//	cs_fmt.Format(_T("%s%s%s"), (b_prefix ? this->Prefix() : _T("")), cs_str.GetString(), (b_suffix ? this->Suffix() : _T("")));
		cs_fmt.Format(_T("%s%s%s"), (_pc_sz)_get_indent(), cs_str.GetString(), (b_suffix ? this->Suffix() : _T("")));
		cs_out += cs_fmt;
	}

	_out() << cs_out;
}

/////////////////////////////////////////////////////////////////////////////

CCache&  CCache::operator +=(_pc_sz _p_out) { if (false == this->Locked()) this->Get().push_back(CString(_p_out)); return *this; };

CCache&  CCache::operator +=(const CString& _str)   { if (false == this->Locked()) this->Get().push_back(_str); return *this; }
CCache&  CCache::operator +=(const TParts& _parts)  { if (false == this->Locked()) 
	// https://en.cppreference.com/w/cpp/container/vector/insert ;
	this->Get().insert(this->Get().end(), _parts.begin(), _parts.end());  // people saying there is no exception for catching, but maybe it's just words;
	return *this;
}
CCache&  CCache::operator +=(TError& _err) { this->Get().push_back(_err.Print(TError::e_print::e_req)); return *this; }

CCache&  CCache::operator <<(_pc_sz _lp_sz_prefix) { this->Prefix(_lp_sz_prefix); return *this; }
CCache&  CCache::operator >>(_pc_sz _lp_sz_suffix) { this->Suffix(_lp_sz_suffix); return *this; }
const
CCache&  CCache::operator ()(void) const { this->Output(); return *this; }
CCache&  CCache::operator ()(const bool _b_verb) { this->Locked() = !_b_verb; return *this; }

CCache::operator bool (void) const { return this->Locked(); }

#pragma endregion
#pragma region cls::CIndent_auto{}

CIndent_auto::CIndent_auto (void) { _get_indent() += 1; }
CIndent_auto::~CIndent_auto (void) { _get_indent() -= 1; }

CIndent_auto::operator _pc_sz (void) const { return _get_indent(); }

#pragma endregion
#pragma region cls::CLogger{}

CLogger::CLogger (void) { __trace::SetTestOut(this); }

const
CCache&  CLogger::Cached  (void) const { return this->m_cache; }
CCache&  CLogger::Cached  (void)       { return this->m_cache; }

_pc_sz   CLogger::Pattern (void) const { return (_pc_sz)this->m_pattern; }
bool     CLogger::Pattern (_pc_sz _lp_sz_pat) {
	_lp_sz_pat;
	bool b_is_set = false;

	if (0 == _lp_sz_pat || 0 == ::_tcslen(_lp_sz_pat))
		return b_is_set;

	this->m_pattern = _lp_sz_pat;
	this->m_pattern.Trim();

	return (b_is_set = !this->m_pattern.IsEmpty());
}

void CLogger::Out (const CString& _str) const {
	this->Out((_pc_sz)_str.GetString());
}

void CLogger::Out (_pc_sz _lp_sz_text) const {
	_lp_sz_text;

	using ms_logger = Microsoft::VisualStudio::CppUnitTestFramework::Logger;

	const bool b_is_pat = this->m_pattern.IsEmpty() == false;
	if (b_is_pat) {

		CString cs_out;
		cs_out.Format(this->Pattern(), _lp_sz_text);
		
		ms_logger::WriteMessage(cs_out.GetString());
	}
	else {
		ms_logger::WriteMessage(_lp_sz_text);
	}

	this->m_cache.Clear();
}

void CLogger::Write (_pc_sz _p_msg) {
	_p_msg;
	if (this->Cached().Locked())
		return;
	CString cs_msg(_p_msg);

	if (-1 != cs_msg.ReverseFind(_T('\n')))
		cs_msg = cs_msg.Left(cs_msg.GetLength() - 1);

	this->Cached().Get().push_back(cs_msg);
}

/////////////////////////////////////////////////////////////////////////////

const CLogger& CLogger::operator << (const CString& _str) const { this->Out(_str); return *this; }
const CLogger& CLogger::operator << (_pc_sz  _lp_sz_text) const { this->Out(_lp_sz_text); return *this; }

CLogger& CLogger::operator +=(const CString& cs_out) { this->Cached() += cs_out; return *this; }
CLogger& CLogger::operator +=(_pc_sz _p_sz_out) { this->Cached() += _p_sz_out; return *this; }
CLogger& CLogger::operator +=(TError& _err) { this->Cached() += _err; return *this; }
CLogger& CLogger::operator >>(_pc_sz _lp_sz_pat) { this->Pattern(_lp_sz_pat); return *this; }

CLogger::operator CCache& (void) { return this->Cached(); }
const
CLogger& CLogger::operator ()(void) const { this->Cached()(); return *this; } 
CLogger& CLogger::operator ()(const bool _b_verb) { this->Cached().Locked() = !_b_verb; return *this; }

CLogger& CLogger::operator ()(TError& _err) {
	_err;
	const bool b_locked = this->Cached().Locked(); // saves the previously set lock option;
	this->Cached().Locked() = false;
	this->Cached() += _err.Print(TError::e_print::e_req);
	this->Cached().Locked() = b_locked;
	return *this;
}

#pragma endregion
#pragma region cls::CTime{}

CTime::CTime (void) {}
_pc_sz CTime::Spent (void) const { return (_pc_sz) this->m_spent; }
_pc_sz CTime::operator ()(void) const { return this->Spent(); }

void CTime::Put (_pc_sz _p_spent) {
	this->m_spent.Format(_T("elapsed %s s."), _p_spent);
}

#pragma endregion

TLogger& _out(void) {
	static
	TLogger logger_;
	return  logger_;
}