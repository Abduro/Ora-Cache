/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2025 at 19:45:12.789, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' vertex attributes' wrapper interface implementation file;
*/
#include "gl_vertex_attr.h"
#include "gl_procs.h"
#include "gl_procs_prog.h"
#include "gl_procs_vertex.h"
#include "program\gl_prog_status.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;
using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {
}}}}

using namespace _impl;

#pragma region __attr_index
CAttr_Location:: CAttr_Location (void) : m_value(CAttr_Location::_$na) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CAttr_Location:: CAttr_Location (const CAttr_Location& _src) : CAttr_Location() { *this = _src; }
CAttr_Location:: CAttr_Location (CAttr_Location&& _victim) : CAttr_Location() { *this = _victim; }
CAttr_Location::~CAttr_Location (void) {}

_pc_sz   CAttr_Location::Attr_name (void) const { return (_pc_sz) this->m_attr_name; }
bool     CAttr_Location::Attr_name (_pc_sz _p_name) {
	_p_name;
	CString cs_name(_p_name); cs_name.Trim();
	const bool b_changed = this->m_attr_name.CompareNoCase((_pc_sz)cs_name);
	if (b_changed)
		this->m_attr_name = cs_name;

	return b_changed;
}

TError&  CAttr_Location::Error (void) const { return this->m_error; }
bool     CAttr_Location::Is_valid (void) const { return this->Value() > CAttr_Location::_$na; }

int32_t  CAttr_Location::Get (void) const {
	if (false == this->Is_valid()) // invalid value set by the CAttr::CIndex::Is_valid() itself if necessary;
		return this->Value();
	else
		return this->m_value = CAttr_Location::Get (this->ProgId(), this->Attr_name(), this->m_error);
}
int32_t  CAttr_Location::Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr_Location::_$na;
	}

	const int32_t n_ndx = __get_attr_procs().GetIndex(_prog_id, _p_att_name);
	if (0 > n_ndx) {
		_err = __get_attr_procs().Error();
	}
	return n_ndx;
}

err_code CAttr_Location::Set (const uint32_t _u_ndx) {
	_u_ndx;
//	if (false == this->Is_valid())
//		return this->Error();

	this->m_error <<__METHOD__<<__s_ok;

	CAttr_Location::Set(this->ProgId(), this->Attr_name(), _u_ndx, this->m_error);
	
	this->m_value = false == this->Error() ? _u_ndx : CAttr_Location::_$na;

	return this->Error();
}
err_code CAttr_Location::Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError& _err) {
	_prog_id; _p_att_name; _err;
	if (0 == _p_att_name || 0 == ::_tcslen(_p_att_name)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: attr name is invalid");
		return CAttr_Location::_$na;
	}
	if (0 == _prog_id) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: _prog_id (0) is invalid");
		return CAttr_Location::_$na;
	}

	if (__failed(__get_attr_procs().SetIndex(_prog_id, _p_att_name, _u_ndx)))
		_err = __get_attr_procs().Error();
	return _err;
}

const
program::CProgId& CAttr_Location::ProgId (void) const { return this->m_prog_id; }
program::CProgId& CAttr_Location::ProgId (void)       { return this->m_prog_id; }

int32_t  CAttr_Location::Value (void) const { return this->m_value; }
bool     CAttr_Location::Value (const uint32_t _n_ndx) {
	_n_ndx;
	const bool b_changed = this->Value() != (int32_t)_n_ndx; if (b_changed) this->m_value = _n_ndx;
	if (b_changed && _n_ndx != CAttr_Location::_$na)
		this->m_error <<__METHOD__<<__s_ok;
	return b_changed;
}

CAttr_Location& CAttr_Location::operator = (const CAttr_Location& _src) { *this << _src.ProgId() << _src.Value() << _src.Attr_name();  return *this; }
CAttr_Location& CAttr_Location::operator = (CAttr_Location&& _victim) { *this = (const CAttr_Location&)_victim; return *this; }
CAttr_Location& CAttr_Location::operator <<(const CProgId& _prog_id) { this->ProgId() << _prog_id; return *this; }
CAttr_Location& CAttr_Location::operator <<(const int32_t _n_value) { this->Value(_n_value); return *this; }
CAttr_Location& CAttr_Location::operator <<(_pc_sz _attr_name) { this->Attr_name(_attr_name); return *this; }
#pragma endregion

/////////////////////////////////////////////////////////////////////////////
#pragma region __vert_attr

using e_att_val_float = ex_ui::draw::open_gl::procs::e_att_val_float;

CAttr:: CAttr (_pc_sz _p_name) : m_size(0), m_type(0), m_norm(false), m_stride (0), m_offset(0), m_used(true) {
	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited;
	if (_p_name) *this << _p_name;
	m_data.resize(0, 0.0f);
}
CAttr:: CAttr (const CAttr& _src) : CAttr() { *this = _src; }
CAttr:: CAttr (CAttr&& _victim) : CAttr() { *this = _victim; }
CAttr::~CAttr (void) {}

const
TAttrData&  CAttr::Data (void) const { return this->m_data; }

TError& CAttr::Error (void) const { return this->m_error; }
bool    CAttr::Is_valid (void) const {
	const uint32_t n_size = static_cast<uint32_t>(this->m_data.size());
	const uint32_t n_req = this->Offset() + this->Size();
	// some operations over vertex data do not require the usage of the program itself, so prog_id should be excluded from the criteria of making validity;
	return false == this->m_name.IsEmpty() /*&& !!this->ProgId()() */&& !(0 == n_size || 0 == n_req || n_req > n_size);
}

bool  CAttr::Is_normal(void) const { return this->m_norm; }
bool  CAttr::Is_normal(const bool _b_norm) { const bool b_changed = this->Is_normal() != _b_norm; if (b_changed) this->m_norm = _b_norm; return b_changed; }
bool  CAttr::Is_used  (void) const { return this->m_used; }
bool  CAttr::Is_used  (const bool _b_used) { const bool b_changed = this->Is_used() != _b_used; if (b_changed) this->m_used = _b_used; return b_changed; }

const
TLocation&  CAttr::Locate (void) const { return this->m_index; }
TLocation&  CAttr::Locate (void)       { return this->m_index; }

_pc_sz   CAttr::Name (void) const { return (_pc_sz)this->m_name; }
err_code CAttr::Name (_pc_sz _p_name) {
	_p_name;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_name(_p_name); cs_name.Trim(); // trimming the input name and removing whitespaces in it look like to be unnecessary;
	if (cs_name.IsEmpty())
		return this->m_error <<__e_inv_arg = _T("An attribute name cannot be empty");
	
	if (this->m_name.Compare((_pc_sz)cs_name)) {
		this->m_name = cs_name;
		this->Locate() << cs_name;
	}
	else
		this->m_error <<__s_false;

	return this->Error();
}

uint32_t CAttr::Offset (void) const { return this->m_offset; }

const
program::CProgId& CAttr::ProgId (void) const { return this->m_prog_id; }
err_code CAttr::ProgId (const uint32_t _prog_id) {
	_prog_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (__failed(this->m_prog_id.Set(_prog_id))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->m_prog_id.Error().Print(TError::e_print::e_req))
		return this->m_error = this->m_prog_id.Error();
	}
	this->Locate().ProgId().Set(_prog_id);

	return this->Error();
}

uint32_t CAttr::Size (void) const { return this->m_size; }
uint32_t CAttr::Type (void) const { return this->m_type; }

uint32_t CAttr::Stride(void) const { return this->m_stride; }

CAttr&  CAttr::operator = (const CAttr& _src) {
	*this << _src.ProgId() << _src.Name() << _src.Locate() << _src.Size() << _src.Type() << _src.Is_normal();
	 this->m_offset = _src.Offset();
	 this->m_stride = _src.Stride();
	 this->m_data   = _src.m_data;
	return *this;
}
CAttr&  CAttr::operator = (CAttr&& _victim) { *this = (const CAttr&) _victim; return *this; }

CAttr&  CAttr::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CAttr&  CAttr::operator <<(const CProgId& _prog_id) { this->ProgId(_prog_id.Get()); return *this; }

CAttr&  CAttr::operator <<(const bool _b_norm)     { this->Is_normal(_b_norm); return *this; }
CAttr&  CAttr::operator <<(const CLocate& _locate) { this->Locate() = _locate; return *this; }
CAttr&  CAttr::operator <<(const uint32_t _u_size) { this->m_size = _u_size; return *this; }
CAttr&  CAttr::operator >>(const uint32_t _u_type) { this->m_type = _u_type; return *this; }

#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region CColor{}
using CConvert = ex_ui::color::rgb::CConvert; // this class has static method for converting color channel to float value;

CColor:: CColor (void) : TBase() {
	TBase::m_error >>__CLASS__<<__s_ok;
	TBase::m_offset = CPosition::Stride(); // it is the count of the position elements and the size of the data type;
	TBase::m_size   = CColor::Channels();  // r|g|b|a;
	TBase::m_stride = CColor::Stride();
	TBase::m_type   = CColor::Type();
	try {
	TBase::m_data.resize(TBase::m_size, 0.0f); TBase::m_data.reserve(TBase::m_size);
	} catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }
}
CColor:: CColor (const CColor& _src) : CColor() { *this = _src; }
CColor:: CColor (CColor&& _victim) : CColor() { *this = _victim; }

const uint32_t CColor::Channels (void) { return 4; } // r|g|b|a;
const uint32_t CColor::Type (void) { return (uint32_t)e_att_val_float::e_float; }
const uint32_t CColor::Stride (void) { return CColor::Channels() * sizeof(float); } // default data type is applied;

void CColor::Set (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	if (TBase::m_data.size() < TBase::Size())
		return;
	
	TBase::m_data[0] = (0.0f > _r ? 0.0f : (1.0f < _r ? 1.0f : _r));
	TBase::m_data[1] = (0.0f > _g ? 0.0f : (1.0f < _g ? 1.0f : _g));
	TBase::m_data[2] = (0.0f > _b ? 0.0f : (1.0f < _b ? 1.0f : _b));
	TBase::m_data[3] = (0.0f > _a ? 0.0f : (1.0f < _a ? 1.0f : _a));
}

void CColor::Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) {
	_r; _g; _b; _a;
	if (TBase::m_data.size() < TBase::Size())
		return;

	// the color channels' sequence: r-g-b-a;
	TBase::m_data[0] = CConvert::ToFloat(_r);
	TBase::m_data[1] = CConvert::ToFloat(_g);
	TBase::m_data[2] = CConvert::ToFloat(_b);
	TBase::m_data[3] = CConvert::ToFloat(_a);
}

void CColor::Set (const rgb_color _rgba) {
	_rgba;
	if (TBase::m_data.size() < TBase::Size())
		return;
	// the color channels' sequence: r-g-b-a;
	TBase::m_data[0] = CConvert::ToFloat(get_r_value(_rgba));
	TBase::m_data[1] = CConvert::ToFloat(get_g_value(_rgba));
	TBase::m_data[2] = CConvert::ToFloat(get_b_value(_rgba));
	TBase::m_data[3] = CConvert::ToFloat(get_a_value(_rgba));
}

CColor&  CColor::operator = (const CColor& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CColor&  CColor::operator = (CColor&& _victim) { *this = (const CColor&)_victim; return *this; }
#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region CPosition{}
CPosition:: CPosition (void) : TBase() {
	TBase::m_error >>__CLASS__<<__s_ok;
	TBase::m_offset = 0; // position goes first, no offset;
	TBase::m_size   = CPosition::Points();
	TBase::m_stride = CPosition::Stride();
	TBase::m_type   = CPosition::Type();
	try {
	TBase::m_data.resize(TBase::m_size, 0.0f); TBase::m_data.reserve(TBase::m_size);
	} catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }
}
CPosition:: CPosition (const CPosition& _src) : CPosition() { *this = _src; }
CPosition:: CPosition (CPosition&& _victim) : CPosition() { *this = _victim; }

const uint32_t CPosition::Points (void) { return 3; } // x|y|z;
const uint32_t CPosition::Type (void) { return (uint32_t)e_att_val_float::e_float; }
const uint32_t CPosition::Stride (void) { return CPosition::Points() * sizeof(float); } // default data type is applied;

void CPosition::Set (const float _x, const float _y, const float _z) {
	_x; _y; _z;
	if (TBase::m_data.size() < TBase::Size())
		return;

	TBase::m_data[0] = (-1.0f > _x ? -1.0f : (1.0f < _x ? 1.0f : _x));
	TBase::m_data[1] = (-1.0f > _y ? -1.0f : (1.0f < _y ? 1.0f : _y));
	TBase::m_data[2] = (-1.0f > _z ? -1.0f : (1.0f < _z ? 1.0f : _z));
}

void CPosition::Set (const long  _x, const long  _y) {
	_x; _y;
}

CPosition&  CPosition::operator = (const CPosition& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CPosition&  CPosition::operator = (CPosition&& _victim) { *this = (const CPosition&)_victim; return *this; }
#pragma endregion
/////////////////////////////////////////////////////////////////////////////

CAttrArray:: CAttrArray (void) { this->m_error <<__CLASS__<<__METHOD__<<__s_ok;
	// sets directly default location values for both attributes;
	 this->Pos().Locate().Value(0); this->Clr().Locate().Value(1);
}
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
#if (0)
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
#endif
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
#if (1)
	static _pc_sz pc_sz_pat_ndx = _T("attr '%s' is bound to ndx = %d;\n");

	CAttr* attrs[] = { &this->Clr(), &this->Pos() };

	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		if (0 > attrs[i_]->Locate().Get()) {
			this->m_error = attrs[i_]->Locate().Error();
			__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		else
			__trace_info_2(pc_sz_pat_ndx, attrs[i_]->Name(), attrs[i_]->Locate().Value());
	}
#endif
	return this->Error();
}
const
CColor&  CAttrArray::Clr (void) const { return this->m_clr; }
CColor&  CAttrArray::Clr (void)       { return this->m_clr; }

uint32_t CAttrArray::Count (void) const { return 2; } // the position and color together make 2;

err_code CAttrArray::Enable (const bool _b_state) {
	_b_state;
	this->m_error <<__METHOD__<<__s_ok;

	CAttr* attrs[] = { &this->Clr(), &this->Pos() };
#if (1)
	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {

		if (false == attrs[i_]->Is_used())
			continue;

		const int32_t n_att_ndx = attrs[i_]->Locate().Value();
		this->Enable(_b_state, n_att_ndx);
	}
#elif (true == false)
	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		const int32_t n_att_ndx = attrs[i_]->Locate().Value();
		if (_b_state) {
			if (__failed(__get_attr_procs().Enable(this->GetId(), n_att_ndx))) {
				this->m_error = __get_attr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is enabled;\n"), n_att_ndx, this->GetId());
			}
		}
		else {
			if (__failed(__get_attr_procs().Disable(this->GetId(), n_att_ndx))) {
				this->m_error = __get_attr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is disabled;\n"), n_att_ndx, this->GetId());
			}
		}
	}
#elif (false == true) // the code snippet below is incorrect;
	const uint32_t _arr_ndx = this->GetId();
	if (__failed(__get_attr_arr_procs().Enable(_arr_ndx))) {
		this->m_error = __get_attr_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(_T("The array: id = %u, ndx = %u is enabled;\n"), this->GetId(), _arr_ndx);
	}
#endif
	return this->Error();
}

err_code CAttrArray::Enable (const bool _b_state, const uint32_t _att_ndx) {
	_b_state; _att_ndx;
	this->m_error <<__METHOD__<<__s_ok;

	if (_b_state) {
		if ( __failed(__get_attr_arr_procs().Enable(_att_ndx))) {
			    this->m_error = __get_attr_procs().Error();
			    __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
		else __trace_info_2(_T("The attr (ndx = %u) of the prog (id = %u) is enabled;\n"), _att_ndx, this->ProgId().Get()); }
	else {
		if ( __failed(__get_attr_arr_procs().Disable(_att_ndx))) {
			    this->m_error = __get_attr_procs().Error();
			    __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
		else __trace_info_2(_T("The attr (ndx = %u) of the prog (id = %u) is disabled;\n"), _att_ndx, this->ProgId().Get());
	}
	return this->Error();
}

err_code CAttrArray::Enum_attrs (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->ProgId().Is_valid()) {
		this->m_error <<__e_inv_arg << _T("Program id is not set");
		__trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); return this->Error();
	}
#if (0)
	int32_t n_count = 0; // actually unsigned integer must be provided because there is no count with value < 0; but original api uses signed int;

	if (__failed(__get_prog_procs().Params(this->ProgId().Get(), (uint32_t)procs::e_prog_params::e_act_attrs, &n_count))) {
	    this->m_error = __get_prog_procs().Error();
	    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); return this->Error();
	}

	CString cs_name;

	for (int32_t i_ = 0; i_ < n_count; i_++) {

		uint32_t n_size = 0; // how mamy elements/components are contained by this attribute;
		uint32_t n_type = 0; // the data type of the attribute, enumeration value;

		if (__failed(__get_attr_procs().GetActive(this->ProgId().Get(), i_, n_size, n_type, cs_name))) {
		    this->m_error = __get_attr_procs().Error();
		    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); break;
		}
	}
#else
	CString cs_name;

	using e_iface = procs::program::e_iface;
	using e_prop  = procs::program::e_prop;

	uint32_t u_prop_cnt = 0;

	if (__failed(__get_iface_procs().Get(this->ProgId().Get(), e_iface::e_prog_in, e_prop::e_active_res, u_prop_cnt))) {
	    this->m_error = __get_attr_procs().Error();
	    __trace_err_2 (_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}

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

		switch (v_values[1]) {
		case 0: { this->Pos().Name((_pc_sz)cs_name); this->Pos().Locate().Value(v_values[1]); } break;  // the position attribute is expected;
		case 1: { this->Clr().Name((_pc_sz)cs_name); this->Clr().Locate().Value(v_values[1]); } break;  // the color attribute is expected;
		}
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
CAttr&   CAttrArray::Item (const uint32_t _ndx) const {
	_ndx;
	if (0 == _ndx) return this->Pos();
	if (1 == _ndx) return this->Clr();

	static CAttr na_attr;
	return na_attr;
}
const
CPosition& CAttrArray::Pos (void) const { return this->m_pos; }
CPosition& CAttrArray::Pos (void)       { return this->m_pos; }

const
program::CProgId& CAttrArray::ProgId (void) const { return this->m_prog_id; }
err_code CAttrArray::ProgId (const uint32_t _prog_id) {
	_prog_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (__failed(this->m_prog_id.Set(_prog_id))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->m_prog_id.Error().Print(TError::e_print::e_req))
		return this->m_error = this->m_prog_id.Error();
	}
	this->Clr().ProgId(_prog_id);
	this->Pos().ProgId(_prog_id);

	return this->Error();
}

uint32_t CAttrArray::Size (void) const { return this->Clr().Size() + this->Pos().Size(); }
uint32_t CAttrArray::Stride (void) const { return this->Clr().Stride() + this->Pos().Stride(); }

CAttrArray&  CAttrArray::operator = (const CAttrArray& _src)  {
	*this << _src.ProgId() << _src.Clr() << _src.Pos(); return *this;
}
CAttrArray&  CAttrArray::operator = (CAttrArray&& _victim) { *this = (const CAttrArray&)_victim; return *this; }

CAttrArray&  CAttrArray::operator <<(const CProgId& _prog_id) { this->ProgId(_prog_id.Get()); return *this; }
CAttrArray&  CAttrArray::operator <<(const uint32_t _prog_id) { this->ProgId(_prog_id); return *this; }

CAttrArray&  CAttrArray::operator <<(const CColor& _clr) { this->Clr() = _clr; return *this; }
CAttrArray&  CAttrArray::operator <<(const CPosition& _pos) { this->Pos() = _pos; return *this;}