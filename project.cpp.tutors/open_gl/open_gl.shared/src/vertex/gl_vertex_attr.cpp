/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2025 at 19:45:12.789, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' vertex attributes' wrapper interface implementation file;
*/
#include "gl_vertex_attr.h"
#include "gl_procs.h"
#include "procs\gl_procs_prog.h"
#include "procs\gl_procs_vertex.h"
#include "program\gl_prog_status.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {
}}}}

using namespace _impl;
#pragma region __attr_index
CAttr::CIndex:: CIndex (const CAttr* _attr_ptr) : m_attr_ptr(_attr_ptr), m_value(CIndex::_$na) {
	this->m_error >>__CLASS__<<__METHOD__<<(this->m_attr_ptr == nullptr ? __e_not_inited : __s_ok);
}
CAttr::CIndex::~CIndex (void) {}

TError&  CAttr::CIndex::Error (void) const { return this->m_error; }

int32_t  CAttr::CIndex::Get (void) const {
	if (false == this->Is_valid()) // invalid value set by the CAttr::CIndex::Is_valid() itself if necessary;
		return this->Value();
	else
		return this->m_value = CAttr::CIndex::Get (this->m_attr_ptr->ProgId(), this->m_attr_ptr->Name(), this->m_error);
}
int32_t  CAttr::CIndex::Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr::CIndex::_$na;
	}

	const int32_t n_ndx = __get_attr_procs().GetIndex(_prog_id, _p_att_name);
	if (0 > n_ndx) {
		_err = __get_attr_procs().Error();
	}
	return n_ndx;
}

bool CAttr::CIndex::Is_valid (void) const {
	this->m_error <<__METHOD__ <<__s_ok;

	if (nullptr == this->m_attr_ptr) { // checks the attribute pointer first;
		this->m_value = CIndex::_$na;
		this->m_error <<__e_pointer;
	}
	
	return false == this->Error();
}

err_code CAttr::CIndex::Set (const uint32_t _u_ndx) {
	_u_ndx;
	if (false == this->Is_valid())
		return this->Error();

	this->m_error <<__METHOD__<<__s_ok;

	CAttr::CIndex::Set(this->m_attr_ptr->ProgId(), this->m_attr_ptr->Name(), _u_ndx, this->m_error);
	
	this->m_value = false == this->Error() ? _u_ndx : CIndex::_$na;

	return this->Error();
}
err_code CAttr::CIndex::Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr::CIndex::_$na;
	}
	if (0 == _prog_id) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: _prog_id (0) is invalid");
		return CAttr::CIndex::_$na;
	}

	if (__failed(__get_attr_procs().SetIndex(_prog_id, _p_att_name, _u_ndx)))
		_err = __get_attr_procs().Error();
	return _err;
}

int32_t  CAttr::CIndex::Value (void) const { return this->m_value; }
bool     CAttr::CIndex::Value (const uint32_t _n_ndx) {
	_n_ndx;
	if (false == this->Is_valid()) // a pointer to attribute is not set;
		return false;

	const bool b_changed = this->Value() != (int32_t)_n_ndx; if (b_changed) this->m_value = _n_ndx;
	return b_changed;
}

int32_t  CAttr::CIndex::operator ()(void) const { return this->Value(); }

CAttr::CIndex&  CAttr::CIndex::operator = (const CAttr::CIndex& _src) { *this << _src.m_attr_ptr << _src.Value(); return *this; }
CAttr::CIndex&  CAttr::CIndex::operator = (CAttr::CIndex&& _victim) { *this = (const CAttr::CIndex&)_victim; return *this; }
CAttr::CIndex&  CAttr::CIndex::operator <<(const CAttr* _p_attr) { this->m_attr_ptr = _p_attr; return *this; }
CAttr::CIndex&  CAttr::CIndex::operator <<(const int32_t _n_value) { this->Value(_n_value); return *this; }

#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region __vert_attr
CAttr:: CAttr (_pc_sz _p_name) : m_index(this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; if (_p_name) *this << _p_name; }
CAttr:: CAttr (const CAttr& _src) : CAttr() { *this = _src; }
CAttr:: CAttr (CAttr&& _victim) : CAttr() { *this = _victim; }
CAttr::~CAttr (void) {}

TError& CAttr::Error (void) const { return this->m_error; }
bool    CAttr::Is_valid (void) const { return false == this->m_name.IsEmpty() && !!this->ProgId()(); }

const
CAttr::CIndex&  CAttr::Index (void) const { return this->m_index; }
CAttr::CIndex&  CAttr::Index (void)       { return this->m_index; }

_pc_sz   CAttr::Name (void) const { return (_pc_sz)this->m_name; }
err_code CAttr::Name (_pc_sz _p_name) {
	_p_name;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_name(_p_name); cs_name.Trim(); // trimming the input name and removing whitespaces in it look like to be unnecessary;
	if (cs_name.IsEmpty())
		return this->m_error <<__e_inv_arg = _T("An attribute name cannot be empty");
	
	if (this->m_name.Compare((_pc_sz)cs_name))
		this->m_name = cs_name;
	else
		this->m_error <<__s_false;

	return this->Error();
}

const
program::CProgId& CAttr::ProgId (void) const { return this->m_prog_id; }
program::CProgId& CAttr::ProgId (void)       { return this->m_prog_id; }

CAttr&  CAttr::operator = (const CAttr& _src) {
	*this << _src.Name(); this->m_prog_id << _src.m_prog_id; this->m_index.Value(_src.m_index.Value());
	return *this;
}

CAttr&  CAttr::operator = (CAttr&& _victim) { *this = (const CAttr&) _victim; return *this; }

CAttr&  CAttr::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CAttr&  CAttr::operator <<(const CProgId& _prog_id) { this->ProgId() << _prog_id; return *this; }
#pragma endregion
/////////////////////////////////////////////////////////////////////////////

CAttrArray:: CAttrArray (void) { this->m_error <<__CLASS__<<__METHOD__<<__s_ok; }
CAttrArray:: CAttrArray (const CAttrArray& _src) : CAttrArray() { *this = _src; }
CAttrArray:: CAttrArray (CAttrArray&& _victim) : CAttrArray() { *this = _victim; }
CAttrArray::~CAttrArray (void) {}

err_code CAttrArray::Bind (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->Error();

	program::CStatus status(this->ProgId());
	// if the program is already linked there is no error should be set, just the warning output to trace;
	if (status.Is_linked()) {
	//	this->m_error <<(err_code)TErrCodes::eExecute::eState = TString().Format(_T("The program (id = %u) is linked;\n"), this->ProgId().Get());
		__trace_warn_2(_T("The program (id = %u) is linked; binding has no effect;\n"), this->ProgId().Get());
	}
	// the sequece of the attributes must be the same as it is in the vertex: 0 - position, 1 - color;
	static _pc_sz pc_sz_pat_ndx = _T("Binding attr '%s' name to ndx = %d succeeded;\n");
	CAttr* attrs[] = { &this->Pos(), &this->Clr() };

	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		if (__failed(attrs[i_]->Index().Set(i_))) {
			this->m_error = attrs[i_]->Index().Error();
			__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		else
			__trace_info_2(pc_sz_pat_ndx, attrs[i_]->Name(), attrs[i_]->Index()());
	}
	return this->Error();
}

err_code CAttrArray::Is_bound (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->Error();

	program::CStatus status(this->ProgId());

	if (false == status.Is_linked()) {
		if (status.Error()) {
			this->m_error = status.Error();
			__trace_err_2(_T("%s\n"), (_pc_sz) status.Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		this->m_error <<(err_code)TErrCodes::eExecute::eState = TString().Format(_T("The program (id = %u) is not linked;\n"), this->ProgId().Get());
		__trace_warn_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	static _pc_sz pc_sz_pat_ndx = _T("attr '%s' is bound to ndx = %d;\n");

	CAttr* attrs[] = { &this->Clr(), &this->Pos() };

	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		if (0 > attrs[i_]->Index().Get()) {
			this->m_error = attrs[i_]->Index().Error();
			__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		else
			__trace_info_2(pc_sz_pat_ndx, attrs[i_]->Name(), attrs[i_]->Index()());
	}
	return this->Error();
}
const
CAttr&   CAttrArray::Clr (void) const { return this->m_clr; }
CAttr&   CAttrArray::Clr (void)       { return this->m_clr; }

err_code CAttrArray::Enum_attrs (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->ProgId().Is_valid()) {
		this->m_error <<__e_inv_arg << _T("Program id is not set");
		__trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); return this->Error();
	}

	int32_t n_count = 0; // actually unsigned integer must be provided because there is no count with value < 0; but original api uses signed int;

	if (__failed(__get_prog_procs().Params(this->ProgId().Get(), (uint32_t)procs::e_prog_params::e_act_attrs, &n_count))) {
	    this->m_error = __get_prog_procs().Error();
	    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); return this->Error();
	}

	CString cs_name;
#if (0)
	for (int32_t i_ = 0; i_ < n_count; i_++) {

		uint32_t n_size = 0; // how mamy elements/components are contained by this attribute;
		uint32_t n_type = 0; // the data type of the attribute, enumeration value;

		if (__failed(__get_attr_procs().GetActive(this->ProgId().Get(), i_, n_size, n_type, cs_name))) {
		    this->m_error = __get_attr_procs().Error();
		    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); break;
		}
	}
#else
	using e_iface = procs::program::e_iface;
	using e_prop  = procs::program::e_prop;

	uint32_t u_prop_cnt = 0;

	if (__failed(__get_iface_procs().Get(this->ProgId().Get(), e_iface::e_prog_in, e_prop::e_active_res, u_prop_cnt))) {
	    this->m_error = __get_attr_procs().Error();
	    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}

	if (this->m_attrs.empty() == false)
	    this->m_attrs.clear();

	this->m_error <<__s_ok; // the error that may occur above is already traced, thus the error state resets;

	procs::program::TRawProps v_props{e_prop::e_arr_size, e_prop::e_location, e_prop::e_name_len, e_prop::e_type};
	procs::program::TRawValues v_values(v_props.size(), 0);

	for (uint32_t i_ = 0; i_ < u_prop_cnt; i_++) {
		if (false == cs_name.IsEmpty()) cs_name.Empty();
		if (false) {}
		else if (__failed(__get_res_procs().GetValues(this->ProgId().Get(), e_iface::e_prog_in, i_, v_props, v_values))) {
			this->m_error = __get_attr_procs().Error();
			__trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
		else if (__failed(__get_res_procs().GetName(this->ProgId().Get(), e_iface::e_prog_in, i_, cs_name))) {
			this->m_error = __get_attr_procs().Error();
			__trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}
		if (this->Error())
			continue;
		CAttr attr;
		attr.Index().Value(v_values[1]);
		attr.Name((_pc_sz)cs_name);
		attr.ProgId() << this->ProgId();
		try {
			this->m_attrs.push_back(attr);
		} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; break; }
	}
#endif
	return this->Error();
}

TError&  CAttrArray::Error (void) const { return this->m_error; }

bool     CAttrArray::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Clr().Is_valid()) {
		this->m_error <<__e_inv_arg = _T("Color attr is not valid;");
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false == this->Error().Is(); // 'false' == 'true' is false;
	}

	if (false == this->Pos().Is_valid()) {
		this->m_error <<__e_inv_arg = _T("Position attr is not valid;");
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false == this->Error().Is(); // 'false' == 'true' is false;
	}

	return false == this->Error().Is();     // 'false' == 'false' is 'true';
}

const
CAttr&   CAttrArray::Pos (void) const { return this->m_pos; }
CAttr&   CAttrArray::Pos (void)       { return this->m_pos; }

const
program::CProgId& CAttrArray::ProgId (void) const { return this->m_prog_id; }
err_code CAttrArray::ProgId (const uint32_t _prog_id) {
	_prog_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (__failed(this->m_prog_id.Set(_prog_id))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->m_prog_id.Error().Print(TError::e_print::e_req))
		return this->m_error = this->m_prog_id.Error();
	}
	this->Clr() << _prog_id;
	this->Pos() << _prog_id;

	return this->Error();
}

CAttrArray&  CAttrArray::operator = (const CAttrArray& _src)  { *this << _src.ProgId() << _src.Pos() >> _src.Clr(); return *this; }
CAttrArray&  CAttrArray::operator = (CAttrArray&& _victim) { *this = (const CAttrArray&)_victim; return *this; }

CAttrArray&  CAttrArray::operator <<(const CProgId& _prog_id) { this->ProgId(_prog_id.Get()); return *this; }
CAttrArray&  CAttrArray::operator <<(const uint32_t _prog_id) { this->ProgId(_prog_id); return *this; }

CAttrArray&  CAttrArray::operator >>(const CAttr& _clr) { this->Clr() = _clr; return *this; }
CAttrArray&  CAttrArray::operator <<(const CAttr& _pos) { this->Pos() = _pos; return *this; }