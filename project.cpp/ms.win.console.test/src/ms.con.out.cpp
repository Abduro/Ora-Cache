/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-May-2024 at 18:07:46.5509336, UTC+7, Novosibirsk, Saturday;
	This Ebo Pack cppunit test console app output interface implementation file;
*/
#include "ms.con.out.h"

using namespace ebo::boo::con;

/////////////////////////////////////////////////////////////////////////////

CCache:: CCache (void) : m_pattern(default_pat){}
CCache::~CCache (void) {}

/////////////////////////////////////////////////////////////////////////////

const TCached& CCache::Get (void) const { return this->m_cached; }
      TCached& CCache::Get (void)       { return this->m_cached; }

_pc_sz CCache::Pattern (void) const { return (_pc_sz)this->m_pattern; }
bool   CCache::Pattern (_pc_sz _pat) {
	_pat;
	bool b_is_set = false;

	if (0 == _pat || 0 == ::_tcslen(_pat))
		return b_is_set;

	this->m_pattern = _pat;
	this->m_pattern.Trim();

	return (b_is_set = !this->m_pattern.IsEmpty());
}

bool   CCache::Append  (_pc_sz _p_sz_item) {
	_p_sz_item;
	bool b_appended = false;

	if (0 == _p_sz_item || 0 == ::_tcslen(_p_sz_item))
		return b_appended;

	this->m_cached.push_back(_p_sz_item);

	return b_appended;
}

void  CCache::Output (void) const {

	for (uint8_t i_ = 0; i_ < this->Get().size(); i_++) {

		if (this->Pattern() == 0) {
			_out_t << TString().Format(default_pat, (_pc_sz)this->Get().at(i_));
		}
		else {
			_out_t << TString().Format(this->Pattern(), (_pc_sz)this->Get().at(i_));
		}
	}

}

/////////////////////////////////////////////////////////////////////////////

CCache& CCache::operator +=(_pc_sz _p_sz_item)   { this->Append(_p_sz_item); return *this; }
CCache& CCache::operator +=(const CString& _str) { this->Append((_pc_sz)_str); return *this; }
CCache& CCache::operator >>(_pc_sz _p_sz_pat)    { this->Pattern(_p_sz_pat); return *this; }
CCache& CCache::operator >>(const CString& _pat) { this->Pattern((_pc_sz)_pat); return *this; }

/////////////////////////////////////////////////////////////////////////////
const
CCache& CCache::operator ()(void) const { this->Output(); return *this; }

/////////////////////////////////////////////////////////////////////////////
const
CCache& COut::Cache (void) const { return this->m_cache; }
CCache& COut::Cache (void)       { return this->m_cache; }

void    COut::Wait (_pc_sz _p_sz_title) {

	if (_p_sz_title) {
		*this << _p_sz_title;
		(*this)();
	}
#if defined(_UNICODE)
	::std::wcin.get();
#else
	::std::cin.get();
#endif
}

/////////////////////////////////////////////////////////////////////////////

COut&   COut::operator <<(const CString& _str) { this->Cache() += _str; return *this; }
COut&   COut::operator <<(_pc_sz _p_sz_item) { this->Cache() += _p_sz_item; return *this; }
const
COut&   COut::operator ()(void) const { this->Cache()(); return *this; }

/////////////////////////////////////////////////////////////////////////////

TOut& ::_out (void) {
	static TOut out_; return out_;
}