/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Nov-2025 at 00:57:38.067, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' vertex attributes' array wrapper interface implementation file;
*/
#include "gl_vertex_arr.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs.h"
#include "procs\gl_procs_vertex.h"
#include "program\gl_prog_status.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;

#pragma region _vert_array

vertex::CArray:: CArray (void) : m_arr_id(0) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
vertex::CArray::~CArray (void) {}

const
vertex::CAttrs&  vertex::CArray::Attrs (void) const { return this->m_attrs; }
vertex::CAttrs&  vertex::CArray::Attrs (void)       { return this->m_attrs; }

err_code vertex::CArray::Bind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (this->Is_bound()) {
#if (0) // no error is set, the array is already bound, so just returns __s_ok;
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("the array of '_arr_id' (%u) is already bound"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
#else
		__trace_warn(_T("The array (id = %u) is already bound;\n"), this->GetId());
#endif
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(this->GetId()))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(_T("The array (id = %u) is bound;\n"), this->GetId());
	}
	return this->Error();
}

bool vertex::CArray::Is_bound (void) const {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	const int32_t n_result = __get_param_procs().GetInt(__gl_arr_bound);
	if (__get_param_procs().Error()) {
		this->m_error = __get_param_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false;
	}
	const bool b_result = this->GetId()== static_cast<uint32_t>(n_result);
	if (false == b_result)
		__trace_info_2(_T("the array of '_arr_id' (%u) is not bound;\n"), this->GetId());

	return b_result;
}

err_code vertex::CArray::Create (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (!!this->GetId()) {
		this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(_T("#__e_inv_state: array (id = %u) already exists"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}
	if (__failed(__get_arr_procs().GetIds(1, &this->m_arr_id))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_impt_2(_T("The vertex array (id = %u) is created;\n"), this->m_arr_id);
	}
	return this->Error();
}

err_code vertex::CArray::Delete (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (0 == this->GetId())  // if the array is not created yet success is returned and just keeping the silence;
		return this->Error();

	if (__failed(__get_arr_procs().Delete(1, &this->m_arr_id))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The vertex array (id = %u) is deleted;\n"), this->m_arr_id);
		this->m_arr_id = 0;
	}
	return this->Error();
}

err_code vertex::CArray::Enable (const bool _b_state) {
	_b_state;
	this->m_error <<__METHOD__<<__s_ok;

	CAttr* attrs[] = { &this->Attrs().Clr(), &this->Attrs().Pos() };

	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		const int32_t n_att_ndx = attrs[i_]->Index().Get();
		if (_b_state) {
			if (__failed(__get_arr_procs().Enable(n_att_ndx))) {
				this->m_error = __get_arr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is enabled;\n"), n_att_ndx, this->GetId());
			}
		}
		else {
			if (__failed(__get_arr_procs().Disable(n_att_ndx))) {
				this->m_error = __get_arr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is disabled;\n"), n_att_ndx, this->GetId());
			}
		}
	}

	return this->Error();
}

TError&  vertex::CArray::Error (void) const { return this->m_error; }

uint32_t vertex::CArray::GetId (void) const { return this->m_arr_id; }

err_code vertex::CArray::Unbind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (false == this->Is_bound()) {
		__trace_info_2(_T("The array id = %u is not bound;\n"), this->GetId());
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(0))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else
		__trace_info_2(_T("The array id = %u is unbound;\n"), this->GetId());

	return this->Error();
}
#pragma endregion

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {
}}}}

using namespace _impl;

/////////////////////////////////////////////////////////////////////////////

CAttr::CIndex:: CIndex (const CAttr& _attr_ref) : m_attr_ref(_attr_ref), m_value(CIndex::_$na) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CAttr::CIndex::~CIndex (void) {}

TError&  CAttr::CIndex::Error (void) const { return this->m_error; }

int32_t  CAttr::CIndex::Get (void) const { return this->m_value = CAttr::CIndex::Get (this->m_attr_ref.ProgId(), this->m_attr_ref.Name(), this->m_error); }
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

err_code CAttr::CIndex::Set (const uint32_t _u_ndx) {

	CAttr::CIndex::Set(this->m_attr_ref.ProgId(), this->m_attr_ref.Name(), _u_ndx, this->m_error);
	
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
int32_t  CAttr::CIndex::operator ()(void) const { return this->Value(); }

/////////////////////////////////////////////////////////////////////////////

CAttr:: CAttr (_pc_sz _p_name) : m_index(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; if (_p_name) *this << _p_name; }
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

CAttr&  CAttr::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CAttr&  CAttr::operator <<(const CProgId& _prog_id) { this->ProgId() << _prog_id; return *this; }

/////////////////////////////////////////////////////////////////////////////

CAttrs:: CAttrs (void) { this->m_error <<__CLASS__<<__METHOD__<<__s_ok; }
CAttrs::~CAttrs (void) {}

err_code CAttrs::Bind (void) {
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

err_code CAttrs::Bound (void) {
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
CAttr&   CAttrs::Clr (void) const { return this->m_clr; }
CAttr&   CAttrs::Clr (void)       { return this->m_clr; }
const
CAttr&   CAttrs::Color (void) const { return this->Clr(); }
CAttr&   CAttrs::Color (void)       { return this->Clr(); }
TError&  CAttrs::Error (void) const { return this->m_error; }

bool     CAttrs::Is_valid (void) const {
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
CAttr&   CAttrs::Pos (void) const { return this->m_pos; }
CAttr&   CAttrs::Pos (void)       { return this->m_pos; }
const
CAttr&   CAttrs::Position (void) const { return this->Pos(); }
CAttr&   CAttrs::Position (void)       { return this->Pos(); }
const
program::CProgId& CAttrs::ProgId (void) const { return this->m_prog_id; }
err_code CAttrs::ProgId (const uint32_t _prog_id) {
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

CAttrs&  CAttrs::operator <<(const CProgId& _prog_id) { this->ProgId(_prog_id.Get()); return *this; }
CAttrs&  CAttrs::operator <<(const uint32_t _prog_id) { this->ProgId(_prog_id); return *this; }