/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Aug-2019 at 7:55:56a, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack shared lite generic XML data elements interface implementation file.
*/
#include "msxml.gen.iface.h"

using namespace shared::xml::ms;

#pragma region cls::CAttr{}

CAttr:: CAttr(void) {}
CAttr::~CAttr(void) {}

const bool   CAttr::Is   (void) const { return m_name.IsEmpty() == false; }
_pc_sz       CAttr::Name (void) const { return m_name.GetString(); }
err_code     CAttr::Name (_pc_sz _v ) {
	if (nullptr == _v || 0 == ::_tcslen( _v)) return __e_inv_arg;
	m_name = _v;
	return __s_ok;
}
CString&     CAttr::Name_Ref (void)   { return m_name ; }
const
_variant_t&  CAttr::Value(void) const { return m_value; }
_variant_t&  CAttr::Value(void)       { return m_value; }

const bool   CAttr::ToBool(const bool _b_def) const {
	if (this->Is() == false)
		return _b_def;
	if (VT_BOOL == m_value.vt)
		return (VARIANT_TRUE == m_value.boolVal);

	CString cs_val = this->ToText();
	if (cs_val.IsEmpty())
		return false;
	else if (0 == cs_val.CompareNoCase(_T("true")))
		return true;
	else if (0 == cs_val.CompareNoCase(_T("false")))
		return false;
	else
		return 0 != ::_tstol(cs_val.GetString());
}
err_code     CAttr::ToBool(const bool _b_val) {
	if (this->Is() == false)
		return __DwordToHresult(ERROR_INVALID_ACCESS);
	m_value.Clear();
	m_value = _b_val;
	return __s_ok;
}

const LONG   CAttr::ToLong(const LONG _l_def) const {
	if (this->Is() == false)
		return _l_def;
	if (VT_I4 == m_value.vt)
		return m_value.lVal;
	_variant_t val_; val_.ChangeType(VT_I4, &m_value);
	return   ( val_.vt == VT_I4 ? val_.lVal : _l_def);
}

err_code     CAttr::ToLong(const LONG _l_val) {
	if (this->Is() == false)
		return __DwordToHresult(ERROR_INVALID_ACCESS);
	m_value.Clear();
	m_value = _l_val;
	return __s_ok;
}

CString      CAttr::ToText(void) const {
	CString cs_val;
	if (this->Is() == false)
		return cs_val;
	if (m_value.vt == VT_BSTR)
		cs_val = m_value.bstrVal;
	else {
		_variant_t val_; val_.ChangeType(VT_BSTR, &m_value);
		cs_val = ( val_.vt == VT_BSTR ? val_.bstrVal : nullptr );
	}
	return cs_val;
}

err_code     CAttr::ToText(_pc_sz lp_sz_val)   {
	if (this->Is() == false)
		return __DwordToHresult(ERROR_INVALID_ACCESS);
	m_value.Clear();
	m_value = lp_sz_val;
	return __s_ok;
}

CAttr::operator CString (void) const { return this->ToText(); }
CAttr::operator const bool (void) const { return this->ToBool(false); }
CAttr::operator const LONG (void) const { return this->ToLong(0); }

const bool  CAttr::operator== (const bool) const { return this->Is(); }
const bool  CAttr::operator== (_pc_sz _lp_sz_name) const {
	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return false;
	else
		return (this->Is() && 0==m_name.CompareNoCase(_lp_sz_name));
}

#if defined(_DEBUG)
CString  CAttr::Print (_pc_sz _lp_sz_sep) const {
	static _pc_sz lp_sz_pat = _T(
		"name = %s; value = %s"
	);
	CString cs_prn; cs_prn.Format(
		lp_sz_pat,
		this->Name(), this->ToText().GetString() 
	); _lp_sz_sep;
	return cs_prn;
}
#endif
#pragma endregion
#pragma region cls::CAttr_Mode{}

CAttr_Mode:: CAttr_Mode(void) : m_b_auto_create(false) {}
CAttr_Mode::~CAttr_Mode(void) {}

const bool&  CAttr_Mode::AutoCreate(void) const { return m_b_auto_create; }
      bool&  CAttr_Mode::AutoCreate(void)       { return m_b_auto_create; }
const
CString&  CAttr_Mode::LastName  (void) const { return m_the_last; }
CString&  CAttr_Mode::LastName  (void)       { return m_the_last; }

CAttr_Mode::operator const bool        (void) const { return this->AutoCreate(); }
CAttr_Mode::operator const CString& (void) const { return this->LastName();   }

CAttr_Mode& CAttr_Mode::operator = (const bool _b_auto_create) { this->AutoCreate() = _b_auto_create; return *this; }
CAttr_Mode& CAttr_Mode::operator = (_pc_sz  _lp_sz_last_name ) { this->LastName() = _lp_sz_last_name; return *this; }

#pragma endregion
#pragma region cls::CAttr_Enum{}

CAttr_Enum:: CAttr_Enum(void) {}
CAttr_Enum::~CAttr_Enum(void) {}

err_code     CAttr_Enum::Add (const CAttr& _att) {
	if (_att.Is() == false)
		return __DwordToHresult(ERROR_INVALID_DATA);
	if (this->Has(_att.Name()))
		return __DwordToHresult(ERROR_ALREADY_EXISTS);
	err_code hr_ = __s_ok;
	try {
		m_atts.insert(
			::std::make_pair(_att.Name(), _att)
		);
	}
	catch (::std::bad_alloc&) {
	}
	return hr_;
}

err_code     CAttr_Enum::Add (_pc_sz lp_sz_name, const _variant_t& _val) {
	CAttr att_;
	att_.Name(lp_sz_name);
	att_.Value() = _val;
	return this->Add(att_);
}

err_code     CAttr_Enum::Del (_pc_sz lp_sz_name) {
	TAttributes::iterator it_ = m_atts.find(CString(lp_sz_name));
	if (it_ == m_atts.end())
		return __DwordToHresult(ERROR_NOT_FOUND);
	try {
		m_atts.erase(it_);
	}
	catch (...) {
		return __DwordToHresult(ERROR_INVALID_ACCESS);
	}
	return __s_ok;
}
const
CAttr&  CAttr_Enum::Get (_pc_sz lp_sz_name) const {
	TAttributes::const_iterator it_ = m_atts.find(CString(lp_sz_name));
	if (it_ == m_atts.end()) {
		static CAttr at_na;
		return at_na;
	}
	else
		return it_->second;
}

CAttr&  CAttr_Enum::Get (_pc_sz lp_sz_name)      {
	TAttributes::iterator it_ = m_atts.find(CString(lp_sz_name));
	if (it_ == m_atts.end()) {
		static CAttr at_na;
		return at_na;
	}
	else
		return it_->second;
}

bool         CAttr_Enum::Has (_pc_sz lp_sz_name) const { return this->Get(lp_sz_name).Is(); }
const
CAttr_Mode&  CAttr_Enum::Mode(void) const { return m_mode; }
CAttr_Mode&  CAttr_Enum::Mode(void)       { return m_mode; }
const
TAttributes& CAttr_Enum::Ref (void) const { return m_atts; }

#if defined(_DEBUG)
CString   CAttr_Enum::Print  (_pc_sz _lp_sz_sep) const {
	static _pc_sz lp_sz_pat = _T(
			"count = % 2u;"
		);
	CString cs_prn; cs_prn.Format(
			lp_sz_pat,
			m_atts.size()
		); _lp_sz_sep;
	for (TAttributes::const_iterator it_ = m_atts.begin(); it_ != m_atts.end(); ++ it_) {
		const CAttr& att_ = it_->second;
		cs_prn += _lp_sz_sep;
		cs_prn += _T(" {");
		cs_prn += att_.Print(_lp_sz_sep);
		cs_prn += _T(";}");
	}
	return cs_prn;
}
#endif

CAttr_Enum& CAttr_Enum::operator += (const CAttr& _att)    { this->Add(_att)      ; return *this; }
CAttr_Enum& CAttr_Enum::operator -= (_pc_sz  lp_sz_name    )    { this->Del(lp_sz_name); return *this; }
CAttr_Enum& CAttr_Enum::operator <= (const bool _b_auto_create) { this->Mode() = _b_auto_create  ; return *this; }
CAttr_Enum& CAttr_Enum::operator <= (_pc_sz  _lp_sz_last_name ) { this->Mode() = _lp_sz_last_name; return *this; }
CAttr_Enum& CAttr_Enum::operator << (const bool _bl_new_value ) {
	_pc_sz lp_sz_the_last = (_pc_sz)m_mode.LastName();
	if (nullptr == lp_sz_the_last)
		return *this;
	CAttr& att_ = this->Get(lp_sz_the_last);
	if (att_.Is())
		att_.ToBool(_bl_new_value);
	return *this;
}
CAttr_Enum& CAttr_Enum::operator << (const LONG _ln_new_value ) {
	_pc_sz lp_sz_the_last = (_pc_sz)m_mode.LastName();
	if (nullptr == lp_sz_the_last)
		return *this;
	CAttr& att_ = this->Get(lp_sz_the_last);
	if (att_.Is())
		att_.ToLong(_ln_new_value);
	return *this;
}

CAttr_Enum::operator const CAttr_Mode& (void) const { return this->Mode(); }
CAttr_Enum::operator       CAttr_Mode& (void)       { return this->Mode(); }

#pragma endregion
#pragma region cls::CNode{}

CNode:: CNode(void) : m_kids(nullptr) { try { m_kids = new CNode_Enum(); } catch(const ::std::bad_alloc&) {} }
CNode:: CNode(const CNode& _ref) : m_kids(nullptr) { try { m_kids = new CNode_Enum(); *this = _ref; } catch(const ::std::bad_alloc&) {} }
CNode::~CNode(void) { if (nullptr != m_kids) try { delete m_kids; m_kids = nullptr; } catch(...){} }

const
CAttr&  CNode::Att (_pc_sz lp_sz_name) const {
	return m_atts.Get(lp_sz_name);
}
const
CNode_Atts&  CNode::Attributes(void) const { return m_atts; }
CNode_Atts&  CNode::Attributes(void)       { return m_atts; }
const
CNode&       CNode::Child     (_pc_sz _lp_sz_name) const    {
	if (nullptr == m_kids || nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name)) {
		static CNode n_a; return n_a;
	}
	else
		return m_kids->Find(_lp_sz_name);
}
const
CNode_Enum*  CNode::Children  (void) const { return m_kids; }
bool         CNode::Is        (void) const { return m_name.IsEmpty() == false; }
bool         CNode::Is        (_pc_sz _lp_sz_name) const {
	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return false;
	else
		return(0 == m_name.CompareNoCase(_lp_sz_name));
}

_pc_sz       CNode::Name      (void) const { return m_name.GetString(); }
err_code     CNode::Name      (_pc_sz  _v) {
	if (nullptr == _v || 0 == ::_tcslen( _v))
		return __DwordToHresult(ERROR_INVALID_DATA);
	m_name = _v;
	return __s_ok;
}
CString&     CNode::Name_Ref  (void)       { return m_name; }
_pc_sz       CNode::Text      (void) const { return m_text.GetString(); }
err_code     CNode::Text      (_pc_sz  _v) {
	if (this->Is() == false)
		return __DwordToHresult(ERROR_INVALID_ACCESS);
	m_text = _v;
	return __s_ok;
}
CString&     CNode::Text_Ref  (void)       { return m_text; }

#if defined(_DEBUG)
CString   CNode::Print     (_pc_sz _lp_sz_sep) const {
	static _pc_sz lp_sz_pat = _T(
		"name  = %s %s"
		"atts  = {%s %s%s }%s"
		"text  = %s %s"
		"kids  = {%s}  "
	);
	CString cs_kids = (nullptr !=  m_kids ? m_kids->Print(_lp_sz_sep).GetString() : _T("#error"));
	CString cs_sep; cs_sep = _lp_sz_sep; if (cs_sep.IsEmpty()) cs_sep = _T("; ");
	CString cs_trim = this->Text();
	CString cs_text = cs_trim.Trim();
	if (cs_text.IsEmpty())
		cs_text = _T("#empty");

	CString cs_out; cs_out.Format(
			lp_sz_pat       ,
			this->Name()    , (_pc_sz)cs_sep , 
			(_pc_sz) cs_sep , (_pc_sz)this->Attributes().Print(_lp_sz_sep), (_pc_sz)cs_sep , (_pc_sz)cs_sep ,
			(_pc_sz) cs_text,
			(_pc_sz) cs_sep ,
			(_pc_sz) cs_kids
		);
	return cs_out;
}
#endif

bool CNode::operator == (_pc_sz lp_sz_name) const {
	if (nullptr == lp_sz_name || 0 == ::_tcslen(lp_sz_name))
		return false;
	else
		return (this->Is() && 0==m_name.CompareNoCase(lp_sz_name));
}

CNode& CNode::operator = (const CNode& _ref) {
	this->Name_Ref()   = _ref.Name();
	this->Attributes() = _ref.Attributes();
	this->Text_Ref()   = _ref.Text();
	if (nullptr != m_kids && nullptr!= _ref.Children()) {
		*m_kids = *(_ref.Children());
	}
	return *this;
}

#pragma endregion
#pragma region cls::CNode_Enum{}

CNode_Enum:: CNode_Enum(void) {}
CNode_Enum:: CNode_Enum(const CNode_Enum& _ref) { *this = _ref; }
CNode_Enum::~CNode_Enum(void) {}

HRESULT CNode_Enum::Add (const CNode& _node) {
	if (_node.Is() == false)
		return __DwordToHresult(ERROR_INVALID_DATA);
	try {
		m_nodes.push_back(_node);
	}
	catch (const ::std::bad_alloc&) {
		return __e_no_memory;
	}
	return __s_ok;
}
const
TNodes  CNode_Enum::Filter(_pc_sz _lp_sz_name) const {
	_lp_sz_name;
	TNodes  nodes_;

	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name)) {
		return nodes_;
	}
	TString s_names; s_names += _lp_sz_name; s_names.MakeLower();
	shared::common::TParts v_names = s_names.Split(_T(";"));

	if (v_names.empty())
		return nodes_;

	for (size_t i_ = 0; i_ < m_nodes.size(); i_++) {
		const CNode& node_ = m_nodes[i_];
		for (size_t j_ = 0; j_ < v_names.size(); j_++) {
			if (node_.Is((_pc_sz)v_names[j_]) == false)
				continue;
			try {
				nodes_.push_back(node_);
			}
			catch(::std::bad_alloc&) {
				return nodes_;
			}
		}
	}
	return nodes_;
}

const CNode&  CNode_Enum::Find(_pc_sz _lp_sz_name) const {
	static CNode not_found;
	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return not_found;
	for (size_t i_ = 0; i_ < m_nodes.size(); i_++) {
		const CNode& node_ = m_nodes[i_];
		if (node_ == _lp_sz_name)
			return node_;
	}
	return not_found;
}

const TNodes& CNode_Enum::Raw (void) const { return m_nodes; }

CNode_Enum& CNode_Enum::operator = (const CNode_Enum& _ref) {
	try {
		for (size_t i_ = 0; i_ < _ref.Raw().size(); i_++) {
			CNode node_ = _ref.Raw()[i_];
			m_nodes.push_back(node_);
		}
	}
	catch (const ::std::bad_alloc&) {
		ATLASSERT(FALSE);
	}
	return *this;
}

#if defined(_DEBUG)
CString   CNode_Enum::Print     (_pc_sz _lp_sz_sep) const {
	static _pc_sz lp_sz_pat = _T(
		"count = % 2u;"
	);
	CString cs_prn; cs_prn.Format(
		lp_sz_pat,
		m_nodes.size()
	); _lp_sz_sep;
	for (size_t i_ = 0; i_ < m_nodes.size(); i_++) {
		const CNode& kid_ =  m_nodes[i_];
		cs_prn += _lp_sz_sep;
		cs_prn += kid_.Print(_lp_sz_sep);
	}
	return cs_prn;
}
#endif
#pragma endregion